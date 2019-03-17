#pragma once

#include "ProcessMemory.hpp"
#include "PESection.hpp"

#include <vector>
#include <Windows.h>

class PEFile
{
private:
	ProcessMemory *pProcessMemory;

	BYTE *pDosStub;
	DWORD DosStubSize;

	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS32 pNTHeader32;
	PIMAGE_NT_HEADERS64 pNTHeader64;

	std::vector<PESection *> Sections;

public:
	PEFile(ProcessMemory *pProcessMemory);
	~PEFile();

	//
	// Functions
	//
	VOID ReadPEHeader();
	VOID SetPEHeaders(PVOID HeaderMemory, DWORD HeaderSize);
	VOID SetSections();

	//
	// Checks
	//
	BOOL IsValidPeFile();
	BOOL IsPE64();
	BOOL IsPE32();

	//
	// Getters
	//
	DWORD GetHeaderSize();
	WORD GetSectionCount();
};

