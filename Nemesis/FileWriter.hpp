#pragma once

#include "PEFile.hpp"

class FileWriter
{
private:
	PEFile *pPEFile;
	HANDLE hFile;

public:
	FileWriter(PEFile *pPEFile);
	~FileWriter();

	BOOL WriteToFile(std::string FileName);
	BOOL WriteMemoryToFile(LONG Offset, DWORD Size, LPCVOID Buffer);
	BOOL WriteZeroMemoryToFile(LONG Offset, DWORD Size);
};

