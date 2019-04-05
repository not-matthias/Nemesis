#include "Module.hpp"

#include <iostream>
#include <algorithm>
#include "Logger.hpp"

Module::Module(ProcessMemory * process_memory)
{
	this->process_memory = process_memory;
	this->base_address = process_memory->GetBaseAddress();
	this->dos_stub = nullptr;
	this->dos_stub_size = 0;
	this->dos_header = nullptr;
	this->nt_header32 = nullptr;
	this->nt_header64 = nullptr;
}

Module::Module(ProcessMemory * process_memory, const DWORD_PTR base_address)
{
	this->process_memory = process_memory;
	this->base_address = base_address;
	this->dos_stub = nullptr;
	this->dos_stub_size = 0;
	this->dos_header = nullptr;
	this->nt_header32 = nullptr;
	this->nt_header64 = nullptr;
}

Module::~Module()
{
	delete dos_stub;
	delete dos_header; // Note: nt headers get set from the dos header (so you delete them too, once you delete the dos header)


	//
	// Delete the section data
	//
	for (auto & section : sections)
	{
		delete[] section.buffer;
	}

	sections.clear();
}


auto Module::Initialize() -> BOOL
{
	Logger::Log("Initializing the module.");

	//
	// Read the header from the Memory
	//
	if (!ReadHeader())
	{
		return FALSE;
	}

	//
	// Set the sections from the Memory
	//
	SetSections();

	return TRUE;
}

auto Module::ReadHeader() -> BOOL
{
	Logger::Log("Reading the headers.");

	const auto header_size = GetHeaderSize();

	//
	// Get the pe header
	//
	const auto header_memory = process_memory->ReadMemory<BYTE *>(base_address, header_size);

	//
	// Check if valid
	//
	if (header_memory == nullptr)
	{
		return FALSE;
	}

	//
	// Set the pe header
	//
	SetHeader(header_memory, header_size);

	return TRUE;
}

auto Module::SetHeader(BYTE * header_memory, const DWORD header_size) -> VOID
{
	Logger::Log("Setting the headers.");

	dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(header_memory);

	//
	// Malformed PE
	//
	if (dos_header->e_lfanew > 0 && dos_header->e_lfanew < static_cast<LONG>(header_size))
	{
		nt_header32 = reinterpret_cast<PIMAGE_NT_HEADERS32>(reinterpret_cast<DWORD_PTR>(dos_header) + dos_header->
			e_lfanew);
		nt_header64 = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<DWORD_PTR>(dos_header) + dos_header->
			e_lfanew);

		if (dos_header->e_lfanew <= static_cast<LONG>(sizeof(IMAGE_DOS_HEADER)))
		{
			dos_stub_size = dos_header->e_lfanew - sizeof(IMAGE_DOS_HEADER);
			dos_stub = reinterpret_cast<BYTE*>(reinterpret_cast<DWORD_PTR>(dos_header) + sizeof(IMAGE_DOS_HEADER));
		}
		else if (dos_header->e_lfanew >= static_cast<LONG>(sizeof(IMAGE_DOS_HEADER)))
		{
			dos_header->e_lfanew = sizeof(IMAGE_DOS_HEADER);
		}
	}
}

auto Module::SetSections() -> VOID
{
	Logger::Log("Setting the sections.");

	auto section_header = IMAGE_FIRST_SECTION(nt_header32);
	Section section;

	sections.clear();
	sections.reserve(GetSectionCount());

	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		//
		// Read section
		//
		if (memcpy_s(&section.section_header, sizeof(IMAGE_SECTION_HEADER), section_header, sizeof(IMAGE_SECTION_HEADER)) != 0)
		{
			std::cout << "Failed to read section." << std::endl;
		}

		//
		// Set the initial memory_size
		//
		section.initial_size = section_header->Misc.VirtualSize;

		// 
		// Calculate the offset
		// 
		const DWORD_PTR read_offset = base_address + section_header->VirtualAddress;

		//
		// Read the section
		//
		if (!ReadSection(section, read_offset))
		{
			std::cout << "Failed to read section." << std::endl;
		}

		//
		// Add it to the list
		//
		sections.push_back(section);
		section_header++;
	}
}

auto Module::SetSectionSize(Section & section, const DWORD_PTR section_pointer) const -> VOID
{
	Logger::Log("Setting the section size.");

	const DWORD max_read_size = 100;
	const auto read_size = section.initial_size;
	auto current_read_size = read_size % max_read_size;

	//
	// Check read memory_size
	//
	if (current_read_size == 0)
	{
		current_read_size = max_read_size;
	}

	//
	// Calculate the new section memory_size
	//
	auto current_offset = section_pointer + read_size - current_read_size;
	while (current_offset >= section_pointer)
	{
		const auto buffer = process_memory->ReadMemory<BYTE *>(current_offset, current_read_size);
		const auto code_byte_count = GetInstructionByteCount(buffer, current_read_size);

		if (code_byte_count != 0)
		{
			current_offset += code_byte_count;

			if (section_pointer < current_offset)
			{
				section.buffer_size = static_cast<DWORD>(current_offset - section_pointer);
				section.buffer_size += 4;

				if (section.initial_size < section.buffer_size)
				{
					section.buffer_size = section.initial_size;
				}
			}

			break;
		}

		current_read_size = max_read_size;
		current_offset -= current_read_size;
	}
}

auto Module::ReadSection(Section & section, const DWORD_PTR section_pointer) const -> BOOL
{
	const DWORD max_read_size = 100;
	const auto read_size = section.initial_size;

	//
	// Check read offset (section without data is valid)
	//
	if (section_pointer == NULL || read_size == 0)
	{
		return TRUE;
	}

	//
	// 
	//
	if (read_size <= max_read_size)
	{
		section.buffer_size = read_size;
		section.buffer = process_memory->ReadMemory<BYTE*>(static_cast<DWORD_PTR>(section_pointer), read_size);
		return TRUE;
	}
	//
	// Set the new section
	//
	SetSectionSize(section, section_pointer);

	//
	//
	//
	if (section.buffer_size != 0)
	{
		section.buffer = process_memory->ReadMemory<BYTE*>(static_cast<DWORD_PTR>(section_pointer), section.buffer_size);
		return TRUE;
	}

	return FALSE;
}


auto Module::SetFileAlignment() const -> VOID
{
	if (Is32Bit())
	{
		nt_header32->OptionalHeader.FileAlignment = file_alignment_constant;
	}
	else
	{
		nt_header64->OptionalHeader.FileAlignment = file_alignment_constant;
	}
}

auto Module::SetEntryPoint(const DWORD_PTR entry_point) const -> VOID
{
	//
	// Calculate the RVA
	//
	const auto entry_point_rva = static_cast<DWORD>(entry_point - base_address);

	//
	// Set the entry point
	// 
	if (Is32Bit())
	{
		nt_header32->OptionalHeader.AddressOfEntryPoint = entry_point_rva;
	}
	else
	{
		nt_header64->OptionalHeader.AddressOfEntryPoint = entry_point_rva;
	}
}

auto Module::AlignSectionHeaders() -> VOID
{
	DWORD section_alignment, file_alignment;

	//
	// Initialize the variables
	//
	if (Is32Bit())
	{
		section_alignment = nt_header32->OptionalHeader.SectionAlignment;
		file_alignment = nt_header32->OptionalHeader.FileAlignment;
	}
	else
	{
		section_alignment = nt_header64->OptionalHeader.SectionAlignment;
		file_alignment = nt_header64->OptionalHeader.FileAlignment;
	}

	//
	// Sort by PointerToRawData (ascending)
	//
	std::sort(sections.begin(), sections.end(), [](const Section & a, const Section & b) -> bool{
		return a.section_header.PointerToRawData < b.section_header.PointerToRawData;
	});

	//
	// Calculate the new file memory_size
	//
	DWORD new_file_size = dos_header->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + nt_header32->FileHeader.SizeOfOptionalHeader +
		(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER));

	//
	// Align the section values
	//
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		// VirtualAddress and VirtualSize
		sections[i].section_header.VirtualAddress = AlignValue(sections[i].section_header.VirtualAddress, section_alignment);
		sections[i].section_header.Misc.VirtualSize = AlignValue(sections[i].section_header.Misc.VirtualSize, section_alignment);

		// PointerToRawData and SizeOfRawData
		sections[i].section_header.PointerToRawData = AlignValue(new_file_size, file_alignment);
		sections[i].section_header.SizeOfRawData = AlignValue(sections[i].buffer_size, file_alignment);

		// NewFileSize
		new_file_size = sections[i].section_header.PointerToRawData + sections[i].section_header.SizeOfRawData;
	}

	//
	// Sort by VirtualAddress (ascending)
	//
	std::sort(sections.begin(), sections.end(), [](const Section & a, const Section & b) -> bool{
		return a.section_header.VirtualAddress < b.section_header.VirtualAddress;
	});
}

auto Module::FixHeader() -> VOID
{
	const DWORD size = dos_header->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER);

	if (Is32Bit())
	{
		//
		// Remove import directories
		//
		nt_header32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		nt_header32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (auto i = nt_header32->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			nt_header32->OptionalHeader.DataDirectory[i].Size = 0;
			nt_header32->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		nt_header32->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		nt_header32->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER32);
		nt_header32->OptionalHeader.SizeOfImage = GetImageSize();
		nt_header32->OptionalHeader.ImageBase = static_cast<DWORD>(base_address);
		nt_header32->OptionalHeader.SizeOfHeaders = AlignValue(size + nt_header32->FileHeader.SizeOfOptionalHeader +
			(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)),
			nt_header32->OptionalHeader.FileAlignment);
	}
	else
	{
		//
		// Remove import directories
		//
		nt_header64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		nt_header64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (auto i = nt_header64->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			nt_header64->OptionalHeader.DataDirectory[i].Size = 0;
			nt_header64->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		nt_header64->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		nt_header64->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);
		nt_header64->OptionalHeader.SizeOfImage = GetImageSize();
		nt_header64->OptionalHeader.ImageBase = static_cast<DWORD>(base_address);
		nt_header64->OptionalHeader.SizeOfHeaders = AlignValue(size + nt_header64->FileHeader.SizeOfOptionalHeader +
			(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)),
			nt_header64->OptionalHeader.FileAlignment);
	}
}

auto Module::RemoveIat() -> VOID
{
	DWORD iat_search_address;

	if (Is32Bit())
	{
		iat_search_address = nt_header32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		nt_header32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		nt_header32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}
	else
	{
		iat_search_address = nt_header64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		nt_header64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		nt_header64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}

	//
	// Find the iat table
	//
	if (iat_search_address)
	{
		for (WORD i = 0; i < GetSectionCount(); i++)
		{
			if ((sections[i].section_header.VirtualAddress <= iat_search_address) &&
				((sections[i].section_header.VirtualAddress + sections[i].section_header.Misc.VirtualSize) >
					iat_search_address))
			{
				//
				// Section must be read and writable
				//
				sections[i].section_header.Characteristics |= IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
			}
		}
	}
}


auto Module::GetInstructionByteCount(const BYTE * data, const DWORD size) -> DWORD
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


auto Module::IsValidModule() const -> BOOL
{
	if (dos_header)
	{
		if (dos_header->e_magic == IMAGE_DOS_SIGNATURE)
		{
			if (nt_header32)
			{
				if (nt_header32->Signature == IMAGE_NT_SIGNATURE)
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
	if (IsValidModule())
	{
		return (nt_header32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);
	}

	return FALSE;
}

auto Module::Is32Bit() const -> BOOL
{
	if (IsValidModule())
	{
		return (nt_header32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
	}

	return FALSE;
}


auto Module::GetImageSize() -> DWORD
{
	DWORD last_virtual_offset = 0, last_virtual_size = 0;
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		if ((sections[i].section_header.VirtualAddress + sections[i].section_header.Misc.VirtualSize) > (last_virtual_offset
			+ last_virtual_size))
		{
			last_virtual_offset = sections[i].section_header.VirtualAddress;
			last_virtual_size = sections[i].section_header.Misc.VirtualSize;
		}
	}

	return last_virtual_size + last_virtual_offset;
}

auto Module::GetSectionCount() const -> WORD
{
	return nt_header32->FileHeader.NumberOfSections;
}

auto Module::GetHeaderSize() -> DWORD
{
	return sizeof(IMAGE_DOS_HEADER) + 0x300 + sizeof(IMAGE_NT_HEADERS64);
}
