#include "PEFile.hpp"

PEFile::PEFile(ProcessMemory *pProcessMemory)
{
	this->pProcessMemory = pProcessMemory;
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
// Functions
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
	PESection *pSection = new PESection;

	Sections.clear();
	Sections.reserve(GetSectionCount());

	for (WORD i = 0; i < GetSectionCount(); i++)
	{
		if (memcpy_s(&pSection->pSectionHeader, sizeof(IMAGE_SECTION_HEADER), pSectionHeader, sizeof(IMAGE_SECTION_HEADER)) != 0)
		{
			std::cout << "Failed to read section." << std::endl;
		}

		Sections.push_back(pSection);
		pSectionHeader++;
	}
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
DWORD PEFile::GetHeaderSize()
{
	return sizeof(IMAGE_DOS_HEADER) + 0x300 + sizeof(IMAGE_NT_HEADERS64);
}

WORD PEFile::GetSectionCount()
{
	return pNTHeader32->FileHeader.NumberOfSections;
}
