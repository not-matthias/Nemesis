#include "Module.hpp"
#include <iostream>

//
// Parse the main module
//
Module::Module(ProcessMemory* process_memory)
{
	this->process_memory_ = process_memory;
	this->base_address_ = process_memory->GetBaseAddress();
}

//
// Parse a custom module
//
Module::Module(ProcessMemory* process_memory, DWORD_PTR base_address)
{
	this->process_memory_ = process_memory;
	this->base_address_ = base_address;
}

Module::~Module()
{
	for (size_t i = 0; i < sections_.size(); i++)
	{
		if (sections_[i].Content)
		{
			delete[] sections_[i].Content;
		}
	}

	sections_.clear();
}

//
// Init Functions
//
auto Module::Initialize() -> BOOL
{
	//
	// Read the header from the memory
	//
	if (!ReadHeader())
	{
		return FALSE;
	}

	//
	// Set the sections from the memory
	//
	SetSections();

	return TRUE;
}

auto Module::ReadHeader() -> BOOL
{
	const auto HeaderSize = GetHeaderSize();

	//
	// Get the pe header
	//
	const auto HeaderMemory = process_memory_->ReadMemory(base_address_, HeaderSize);

	//
	// Check if valid
	//
	if (HeaderMemory == nullptr)
	{
		return FALSE;
	}

	//
	// Set the pe header
	//
	SetHeader(HeaderMemory, HeaderSize);

	return TRUE;
}

auto Module::SetHeader(PVOID const header_memory, const DWORD header_size) -> VOID
{
	dos_header_ = static_cast<PIMAGE_DOS_HEADER>(header_memory);

	//
	// Malformed PE
	//
	if (dos_header_->e_lfanew > 0 && dos_header_->e_lfanew < static_cast<LONG>(header_size))
	{
		nt_header32_ = reinterpret_cast<PIMAGE_NT_HEADERS32>(reinterpret_cast<DWORD_PTR>(dos_header_) + dos_header_->
			e_lfanew);
		nt_header64_ = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<DWORD_PTR>(dos_header_) + dos_header_->
			e_lfanew);

		if (dos_header_->e_lfanew > sizeof(IMAGE_DOS_HEADER))
		{
			dos_stub_size_ = dos_header_->e_lfanew - sizeof(IMAGE_DOS_HEADER);
			dos_stub_ = reinterpret_cast<BYTE *>(reinterpret_cast<DWORD_PTR>(dos_header_) + sizeof(IMAGE_DOS_HEADER));
		}
		else if (dos_header_->e_lfanew < sizeof(IMAGE_DOS_HEADER))
		{
			dos_header_->e_lfanew = sizeof(IMAGE_DOS_HEADER);
		}
	}
}

auto Module::SetSections() -> VOID
{
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNTHeader32);
	PESection Section;

	sections_.clear();
	sections_.reserve(GetSectionCount());

	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		//
		// Read section
		//
		if (memcpy_s(&Section.SectionHeader, sizeof(IMAGE_SECTION_HEADER), pSectionHeader,
		             sizeof(IMAGE_SECTION_HEADER)) != 0)
		{
			std::cout << "Failed to read section." << std::endl;
		}

		//
		// Set the initial size
		//
		Section.InitialSize = pSectionHeader->Misc.VirtualSize;

		// 
		// Calculate the offset
		// 
		DWORD_PTR ReadOffset = base_address_ + pSectionHeader->VirtualAddress;

		//
		// Read the section
		//
		if (!ReadSection(Section, ReadOffset))
		{
			std::cout << "Failed to read section." << std::endl;
		}

		//
		// Add it to the list
		//
		sections_.push_back(Section);
		pSectionHeader++;
	}
}

auto Module::SetSectionSize(PESection& section, const DWORD_PTR section_pointer) const -> VOID
{
	DWORD MaxReadSize = 100;
	DWORD ReadSize = section.InitialSize;
	DWORD CurrentReadSize = ReadSize % MaxReadSize;

	//
	// Check read size
	//
	if (CurrentReadSize == 0)
	{
		CurrentReadSize = MaxReadSize;
	}

	//
	// Calculate the new section size
	//
	DWORD_PTR CurrentOffset = section_pointer + ReadSize - CurrentReadSize;
	while (CurrentOffset >= section_pointer)
	{
		BYTE* Buffer = reinterpret_cast<BYTE *>(process_memory_->ReadMemory(CurrentOffset, CurrentReadSize));
		DWORD CodeByteCount = GetInstructionByteCount(Buffer, CurrentReadSize);

		if (CodeByteCount != 0)
		{
			CurrentOffset += CodeByteCount;

			if (section_pointer < CurrentOffset)
			{
				section.DataSize = static_cast<DWORD>(CurrentOffset - section_pointer);
				section.DataSize += 4;

				if (section.InitialSize < section.DataSize)
				{
					section.DataSize = section.InitialSize;
				}
			}

			break;
		}

		CurrentReadSize = MaxReadSize;
		CurrentOffset -= CurrentReadSize;
	}
}

auto Module::ReadSection(PESection& section, const DWORD_PTR section_pointer) const -> BOOL
{
	const DWORD MaxReadSize = 100;
	const auto ReadSize = section.InitialSize;

	//
	// Check read offset (section without data is valid)
	//
	if (section_pointer == NULL || ReadSize == 0)
	{
		return TRUE;
	}

	//
	// 
	//
	if (ReadSize <= MaxReadSize)
	{
		section.DataSize = ReadSize;
		section.Content = process_memory_->ReadMemory(static_cast<DWORD_PTR>(section_pointer), ReadSize);
		return TRUE;
	}
	//
	// Set the new section
	//
	SetSectionSize(section, section_pointer);

	//
	//
	//
	if (section.DataSize != 0)
	{
		section.Content = process_memory_->ReadMemory(static_cast<DWORD_PTR>(section_pointer), section.DataSize);
		return TRUE;
	}

	return FALSE;
}


//
// Functions
//
auto Module::SetFileAlignment() const -> VOID
{
	if (Is32Bit())
	{
		nt_header32_->OptionalHeader.FileAlignment = FileAlignmentConstant;
	}
	else
	{
		nt_header64_->OptionalHeader.FileAlignment = FileAlignmentConstant;
	}
}

auto Module::SetEntryPoint(DWORD_PTR entry_point) const -> VOID
{
	//
	// Calculate the RVA
	//
	DWORD EntryPointRVA = (DWORD)(entry_point - base_address_);

	//
	// Set the entry point
	// 
	if (Is32Bit())
	{
		nt_header32_->OptionalHeader.AddressOfEntryPoint = EntryPointRVA;
	}
	else
	{
		nt_header64_->OptionalHeader.AddressOfEntryPoint = EntryPointRVA;
	}
}

auto Module::AlignSectionHeaders() -> VOID
{
	DWORD SectionAlignment = 0, FileAlignment = 0, NewFileSize = 0;

	//
	// Initialize the variables
	//
	if (Is32Bit())
	{
		SectionAlignment = nt_header32_->OptionalHeader.SectionAlignment;
		FileAlignment = nt_header32_->OptionalHeader.FileAlignment;
	}
	else
	{
		SectionAlignment = nt_header64_->OptionalHeader.SectionAlignment;
		FileAlignment = nt_header64_->OptionalHeader.FileAlignment;
	}

	//
	// Sort by PointerToRawData (ascending)
	//
	std::sort(sections_.begin(), sections_.end(), [](const PESection& a, const PESection& b) -> bool
	{
		return a.SectionHeader.PointerToRawData < b.SectionHeader.PointerToRawData;
	});

	//
	// Calculate the new file size
	//
	NewFileSize = dos_header_->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + nt_header32_
	                                                                                 ->FileHeader.SizeOfOptionalHeader +
		(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER));

	//
	// Align the section values
	//
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		// VirtualAddress and VirtualSize
		sections_[i].SectionHeader.VirtualAddress = AlignValue(sections_[i].SectionHeader.VirtualAddress,
		                                                      SectionAlignment);
		sections_[i].SectionHeader.Misc.VirtualSize = AlignValue(sections_[i].SectionHeader.Misc.VirtualSize,
		                                                        SectionAlignment);

		// PointerToRawData and SizeOfRawData
		sections_[i].SectionHeader.PointerToRawData = AlignValue(NewFileSize, FileAlignment);
		sections_[i].SectionHeader.SizeOfRawData = AlignValue(sections_[i].DataSize, FileAlignment);

		// NewFileSize
		NewFileSize = sections_[i].SectionHeader.PointerToRawData + sections_[i].SectionHeader.SizeOfRawData;
	}

	//
	// Sort by VirtualAddress (ascending)
	//
	std::sort(sections_.begin(), sections_.end(), [](const PESection& a, const PESection& b) -> bool
	{
		return a.SectionHeader.VirtualAddress < b.SectionHeader.VirtualAddress;
	});
}

auto Module::FixHeader() -> VOID
{
	DWORD dwSize = dos_header_->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER);

	if (Is32Bit())
	{
		//
		// Remove import directories
		//
		nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (DWORD i = nt_header32_->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			nt_header32_->OptionalHeader.DataDirectory[i].Size = 0;
			nt_header32_->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		nt_header32_->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		nt_header32_->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER32);
		nt_header32_->OptionalHeader.SizeOfImage = GetImageSize();
		nt_header32_->OptionalHeader.ImageBase = static_cast<DWORD>(base_address_);
		nt_header32_->OptionalHeader.SizeOfHeaders = AlignValue(dwSize + nt_header32_->FileHeader.SizeOfOptionalHeader +
		                                                       (GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)),
		                                                       nt_header32_->OptionalHeader.FileAlignment);
	}
	else
	{
		//
		// Remove import directories
		//
		nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (DWORD i = nt_header64_->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			nt_header64_->OptionalHeader.DataDirectory[i].Size = 0;
			nt_header64_->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		nt_header64_->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		nt_header64_->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);
		nt_header64_->OptionalHeader.SizeOfImage = GetImageSize();
		nt_header64_->OptionalHeader.ImageBase = static_cast<DWORD>(base_address_);
		nt_header64_->OptionalHeader.SizeOfHeaders = AlignValue(dwSize + nt_header64_->FileHeader.SizeOfOptionalHeader +
		                                                       (GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)),
		                                                       nt_header64_->OptionalHeader.FileAlignment);
	}
}

auto Module::RemoveIat() -> VOID
{
	DWORD IATSearchAddress = 0;

	if (Is32Bit())
	{
		IATSearchAddress = nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		nt_header32_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}
	else
	{
		IATSearchAddress = nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		nt_header64_->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}

	//
	// Find the iat table
	//
	if (IATSearchAddress)
	{
		for (WORD i = 0; i < GetSectionCount(); i++)
		{
			if ((sections_[i].SectionHeader.VirtualAddress <= IATSearchAddress) &&
				((sections_[i].SectionHeader.VirtualAddress + sections_[i].SectionHeader.Misc.VirtualSize) >
					IATSearchAddress))
			{
				//
				// Section must be read and writable
				//
				sections_[i].SectionHeader.Characteristics |= IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
			}
		}
	}
}


auto Module::GetInstructionByteCount(const BYTE* data, const DWORD size) -> DWORD
{
	//
	// Check if null
	//
	if (data == nullptr)
	{
		return 0;
	}

	//
	// Calculate instruction count
	//
	for (int i = (size - 1); i >= 0; i--)
	{
		if (data[i] != 0)
		{
			return i + 1;
		}
	}

	return 0;
}

auto Module::AlignValue(const DWORD bad_value, const DWORD align_to) -> DWORD
{
	return (((bad_value + align_to - 1) / align_to) * align_to);
}


//
// Checks
//
auto Module::IsValidPeFile() const -> BOOL
{
	if (dos_header_)
	{
		if (dos_header_->e_magic == IMAGE_DOS_SIGNATURE)
		{
			if (nt_header32_)
			{
				if (nt_header32_->Signature == IMAGE_NT_SIGNATURE)
				{
					return true;
				}
			}
		}
	}

	return false;
}

auto Module::Is64Bit() const -> BOOL
{
	if (IsValidPeFile())
	{
		return (nt_header32_->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);
	}

	return FALSE;
}

auto Module::Is32Bit() const -> BOOL
{
	if (IsValidPeFile())
	{
		return (nt_header32_->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
	}

	return FALSE;
}


//
// Getters
//
auto Module::GetImageSize() -> DWORD
{
	DWORD lastVirtualOffset = 0, lastVirtualSize = 0;
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		if ((sections_[i].SectionHeader.VirtualAddress + sections_[i].SectionHeader.Misc.VirtualSize) > (lastVirtualOffset
			+ lastVirtualSize))
		{
			lastVirtualOffset = sections_[i].SectionHeader.VirtualAddress;
			lastVirtualSize = sections_[i].SectionHeader.Misc.VirtualSize;
		}
	}

	return lastVirtualSize + lastVirtualOffset;
}

auto Module::GetHeaderSize() const -> DWORD
{
	return sizeof(IMAGE_DOS_HEADER) + 0x300 + sizeof(IMAGE_NT_HEADERS64);
}

auto Module::GetSectionCount() const -> WORD
{
	return nt_header32_->FileHeader.NumberOfSections;
}
