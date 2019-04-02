#pragma once

#include "ProcessMemory.hpp"
#include "PESection.hpp"

#include <algorithm>
#include <vector>
#include <Windows.h>

class PEFile
{
private:
	ProcessMemory *pProcessMemory;
	DWORD_PTR BaseAddress;

public:
	const DWORD FileAlignmentConstant = 0x200;

	BYTE *pDosStub;
	DWORD DosStubSize;

	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS32 pNTHeader32;
	PIMAGE_NT_HEADERS64 pNTHeader64;

	std::vector<PESection> Sections;

private:
	//
	// Init Functions
	//
	BOOL ReadPEHeader();
	VOID SetPEHeaders(PVOID HeaderMemory, DWORD HeaderSize);
	VOID SetSections();
	VOID SetSectionSize(PESection &Section, const DWORD_PTR ReadOffset);
	BOOL ReadSection(PESection &Section, const DWORD_PTR ReadOffset);

public:
	PEFile(ProcessMemory *pProcessMemory);
	PEFile(ProcessMemory *pProcessMemory, DWORD_PTR BaseAddress);
	~PEFile();

	//
	// Functions
	//
	BOOL Initialize();

	VOID SetFileAlignment();
	VOID SetEntryPoint(DWORD_PTR EntryPoint);
	VOID AlignSectionHeaders();
	VOID FixPEHeader();
	VOID RemoveIAT();

	DWORD GetInstructionByteCount(BYTE *Data, DWORD Size);
	DWORD AlignValue(DWORD BadValue, DWORD AlignTo);

	//
	// Checks
	//
	BOOL IsValidPeFile();
	BOOL IsPE64();
	BOOL IsPE32();

	//
	// Getters
	//
	DWORD GetImageSize();
	DWORD GetHeaderSize();
	WORD GetSectionCount();
};

