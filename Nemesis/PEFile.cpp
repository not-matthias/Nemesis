#include "PEFile.hpp"

PEFile::PEFile(ProcessMemory *pProcessMemory)
{
	this->pProcessMemory = pProcessMemory;

	//
	// Initialize the PEFile
	//
	ReadPEHeader();
	SetSections();
}

PEFile::~PEFile()
{
	// FIXME: Add cleanup here
	//for (size_t i = 0; i < Sections.size(); i++)
	//{
	//	if (Sections[i]->pData)
	//	{
	//		delete[] Sections[i]->pData;
	//	}
	//}

	//Sections.clear();
}

//
// Init Functions
//
VOID PEFile::ReadPEHeader()
{
	DWORD HeaderSize = GetHeaderSize();

	//
	// Get the pe header
	//
	PVOID HeaderMemory = pProcessMemory->ReadMemory(pProcessMemory->GetBaseAddress(), HeaderSize);

	//
	// Set the pe header
	//
	SetPEHeaders(HeaderMemory, HeaderSize);
}

VOID PEFile::SetPEHeaders(PVOID HeaderMemory, DWORD HeaderSize)
{
	pDosHeader = (PIMAGE_DOS_HEADER)HeaderMemory;

	//
	// Malformed PE
	//
	if (pDosHeader->e_lfanew > 0 && pDosHeader->e_lfanew < static_cast<LONG>(HeaderSize))
	{
		pNTHeader32 = (PIMAGE_NT_HEADERS32)((DWORD_PTR)pDosHeader + pDosHeader->e_lfanew);
		pNTHeader64 = (PIMAGE_NT_HEADERS64)((DWORD_PTR)pDosHeader + pDosHeader->e_lfanew);

		if (pDosHeader->e_lfanew > sizeof(IMAGE_DOS_HEADER))
		{
			DosStubSize = pDosHeader->e_lfanew - sizeof(IMAGE_DOS_HEADER);
			pDosStub = (BYTE *)((DWORD_PTR)pDosHeader + sizeof(IMAGE_DOS_HEADER));
		}
		else if (pDosHeader->e_lfanew < sizeof(IMAGE_DOS_HEADER))
		{
			pDosHeader->e_lfanew = sizeof(IMAGE_DOS_HEADER);
		}
	}

}

VOID PEFile::SetSections()
{
	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNTHeader32);
	PESection Section;

	Sections.clear();
	Sections.reserve(GetSectionCount());

	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		//
		// Read section
		//
		if (memcpy_s(&Section.SectionHeader, sizeof(IMAGE_SECTION_HEADER), pSectionHeader, sizeof(IMAGE_SECTION_HEADER)) != 0)
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
		DWORD_PTR ReadOffset = pProcessMemory->GetBaseAddress() + pSectionHeader->VirtualAddress;

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
		Sections.push_back(Section);
		pSectionHeader++;
	}
}

//
// Functions
//
VOID PEFile::SetFileAlignment()
{
	if (IsPE32())
	{
		pNTHeader32->OptionalHeader.FileAlignment = FileAlignmentConstant;
	}
	else
	{
		pNTHeader64->OptionalHeader.FileAlignment = FileAlignmentConstant;
	}
}

VOID PEFile::SetEntryPoint(DWORD_PTR EntryPoint)
{
	//
	// Calculate the RVA
	//
	DWORD EntryPointRVA = (DWORD)(EntryPoint - pProcessMemory->GetBaseAddress());

	//
	// Set the entry point
	// 
	if (IsPE32())
	{
		pNTHeader32->OptionalHeader.AddressOfEntryPoint = EntryPointRVA;
	}
	else
	{
		pNTHeader64->OptionalHeader.AddressOfEntryPoint = EntryPointRVA;
	}
}

VOID PEFile::AlignSectionHeaders()
{
	DWORD SectionAlignment = 0, FileAlignment = 0, NewFileSize = 0;

	//
	// Initialize the variables
	//
	if (IsPE32())
	{
		SectionAlignment = pNTHeader32->OptionalHeader.SectionAlignment;
		FileAlignment = pNTHeader32->OptionalHeader.FileAlignment;
	}
	else
	{
		SectionAlignment = pNTHeader64->OptionalHeader.SectionAlignment;
		FileAlignment = pNTHeader64->OptionalHeader.FileAlignment;
	}

	//
	// Sort by PointerToRawData (ascending)
	//
	std::sort(Sections.begin(), Sections.end(), [](const PESection & a, const PESection & b) -> bool
	{
		return a.SectionHeader.PointerToRawData < b.SectionHeader.PointerToRawData;
	});

	//
	// Calculate the new file size
	//
	NewFileSize = pDosHeader->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER) + pNTHeader32->FileHeader.SizeOfOptionalHeader + (GetSectionCount() * sizeof(IMAGE_SECTION_HEADER));

	//
	// Align the section values
	//
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		// VirtualAddress and VirtualSize
		Sections[i].SectionHeader.VirtualAddress = AlignValue(Sections[i].SectionHeader.VirtualAddress, SectionAlignment);
		Sections[i].SectionHeader.Misc.VirtualSize = AlignValue(Sections[i].SectionHeader.Misc.VirtualSize, SectionAlignment);

		// PointerToRawData and SizeOfRawData
		Sections[i].SectionHeader.PointerToRawData = AlignValue(NewFileSize, FileAlignment);
		Sections[i].SectionHeader.SizeOfRawData = AlignValue(Sections[i].DataSize, FileAlignment);

		// NewFileSize
		NewFileSize = Sections[i].SectionHeader.PointerToRawData + Sections[i].SectionHeader.SizeOfRawData;
	}

	//
	// Sort by VirtualAddress (ascending)
	//
	std::sort(Sections.begin(), Sections.end(), [](const PESection & a, const PESection & b) -> bool
	{
		return a.SectionHeader.VirtualAddress < b.SectionHeader.VirtualAddress;
	});
}

VOID PEFile::FixPEHeader()
{
	DWORD dwSize = pDosHeader->e_lfanew + sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER);

	if (IsPE32())
	{
		//
		// Remove import directories
		//
		pNTHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		pNTHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (DWORD i = pNTHeader32->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			pNTHeader32->OptionalHeader.DataDirectory[i].Size = 0;
			pNTHeader32->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		pNTHeader32->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		pNTHeader32->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER32);
		pNTHeader32->OptionalHeader.SizeOfImage = GetImageSize();
		pNTHeader32->OptionalHeader.ImageBase = static_cast<DWORD>(pProcessMemory->GetBaseAddress());
		pNTHeader32->OptionalHeader.SizeOfHeaders = AlignValue(dwSize + pNTHeader32->FileHeader.SizeOfOptionalHeader +
			(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)), pNTHeader32->OptionalHeader.FileAlignment);
	}
	else
	{
		//
		// Remove import directories
		//
		pNTHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].VirtualAddress = 0;
		pNTHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT].Size = 0;

		for (DWORD i = pNTHeader64->OptionalHeader.NumberOfRvaAndSizes; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
		{
			pNTHeader64->OptionalHeader.DataDirectory[i].Size = 0;
			pNTHeader64->OptionalHeader.DataDirectory[i].VirtualAddress = 0;
		}

		// 
		// Set the sizes and base address
		// 
		pNTHeader64->OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;
		pNTHeader64->FileHeader.SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);
		pNTHeader64->OptionalHeader.SizeOfImage = GetImageSize();
		pNTHeader64->OptionalHeader.ImageBase = static_cast<DWORD>(pProcessMemory->GetBaseAddress());
		pNTHeader64->OptionalHeader.SizeOfHeaders = AlignValue(dwSize + pNTHeader64->FileHeader.SizeOfOptionalHeader +
			(GetSectionCount() * sizeof(IMAGE_SECTION_HEADER)), pNTHeader64->OptionalHeader.FileAlignment);
	}
}

VOID PEFile::RemoveIAT()
{
	DWORD IATSearchAddress = 0;

	if (IsPE32())
	{
		IATSearchAddress = pNTHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		pNTHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		pNTHeader32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}
	else
	{
		IATSearchAddress = pNTHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress;
		pNTHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress = 0;
		pNTHeader64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size = 0;
	}

	//
	// Find the iat table
	//
	if (IATSearchAddress)
	{
		for (WORD i = 0; i < GetSectionCount(); i++)
		{
			if ((Sections[i].SectionHeader.VirtualAddress <= IATSearchAddress) &&
				((Sections[i].SectionHeader.VirtualAddress + Sections[i].SectionHeader.Misc.VirtualSize) > IATSearchAddress))
			{
				//
				// Section must be read and writable
				//
				Sections[i].SectionHeader.Characteristics |= IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_WRITE;
			}
		}
	}
}

// WORKING
VOID PEFile::SetSectionSize(PESection &Section, const DWORD_PTR SectionPointer)
{
	DWORD MaxReadSize = 100;
	DWORD ReadSize = Section.InitialSize;
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
	DWORD_PTR CurrentOffset = SectionPointer + ReadSize - CurrentReadSize;
	while (CurrentOffset >= SectionPointer)
	{
		BYTE *Buffer = reinterpret_cast<BYTE *>(pProcessMemory->ReadMemory(CurrentOffset, CurrentReadSize));
		DWORD CodeByteCount = GetInstructionByteCount(Buffer, CurrentReadSize);

		if (CodeByteCount != 0)
		{
			CurrentOffset += CodeByteCount;

			if (SectionPointer < CurrentOffset)
			{
				Section.DataSize = static_cast<DWORD>(CurrentOffset - SectionPointer);
				Section.DataSize += 4;

				if (Section.InitialSize < Section.DataSize)
				{
					Section.DataSize = Section.InitialSize;
				}
			}

			break;
		}

		CurrentReadSize = MaxReadSize;
		CurrentOffset -= CurrentReadSize;
	}
}

// WORKING
BOOL PEFile::ReadSection(PESection &Section, const DWORD_PTR SectionPointer)
{
	DWORD MaxReadSize = 100;
	DWORD ReadSize = Section.InitialSize;

	//
	// Check read offset (section without data is valid)
	//
	if (SectionPointer == NULL || ReadSize == 0)
	{
		return TRUE;
	}

	//
	// 
	//
	if (ReadSize <= MaxReadSize)
	{
		Section.DataSize = ReadSize;
		Section.Content = pProcessMemory->ReadMemory(static_cast<DWORD_PTR>(SectionPointer), ReadSize);
		return TRUE;
	}
	else
	{
		//
		// Set the new section
		//
		SetSectionSize(Section, SectionPointer);

		//
		//
		//
		if (Section.DataSize != 0)
		{
			Section.Content = pProcessMemory->ReadMemory(static_cast<DWORD_PTR>(SectionPointer), Section.DataSize);
			return TRUE;
		}
	}

	return FALSE;
}

DWORD PEFile::GetInstructionByteCount(BYTE * Data, DWORD Size)
{
	//
	// Check if null
	//
	if (Data == nullptr)
	{
		return 0;
	}

	//
	// Calculate instruction count
	//
	for (int i = (Size - 1); i >= 0; i--)
	{
		if (Data[i] != 0)
		{
			return i + 1;
		}
	}

	return 0;
}

DWORD PEFile::AlignValue(DWORD BadValue, DWORD AlignTo)
{
	return (((BadValue + AlignTo - 1) / AlignTo) * AlignTo);
}


//
// Checks
//
BOOL PEFile::IsValidPeFile()
{
	if (pDosHeader)
	{
		if (pDosHeader->e_magic == IMAGE_DOS_SIGNATURE)
		{
			if (pNTHeader32)
			{
				if (pNTHeader32->Signature == IMAGE_NT_SIGNATURE)
				{
					return true;
				}
			}
		}
	}

	return false;
}

BOOL PEFile::IsPE64()
{
	if (IsValidPeFile())
	{
		return (pNTHeader32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC);
	}

	return FALSE;
}

BOOL PEFile::IsPE32()
{
	if (IsValidPeFile())
	{
		return (pNTHeader32->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC);
	}

	return FALSE;
}


//
// Getters
//
DWORD PEFile::GetImageSize()
{
	DWORD lastVirtualOffset = 0, lastVirtualSize = 0;
	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		if ((Sections[i].SectionHeader.VirtualAddress + Sections[i].SectionHeader.Misc.VirtualSize) > (lastVirtualOffset + lastVirtualSize))
		{
			lastVirtualOffset = Sections[i].SectionHeader.VirtualAddress;
			lastVirtualSize = Sections[i].SectionHeader.Misc.VirtualSize;
		}
	}

	return lastVirtualSize + lastVirtualOffset;
}

DWORD PEFile::GetHeaderSize()
{
	return sizeof(IMAGE_DOS_HEADER) + 0x300 + sizeof(IMAGE_NT_HEADERS64);
}

WORD PEFile::GetSectionCount()
{
	return pNTHeader32->FileHeader.NumberOfSections;
}
