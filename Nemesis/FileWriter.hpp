#pragma once

#include "PEFile.hpp"

#include <vector>

class FileWriter
{
private:
	std::string FileName;
	HANDLE hFile;

public:
	FileWriter(std::string FileName);
	~FileWriter();

	BOOL WriteToFile(PEFile *pPEFile);
	BOOL WriteMemoryToNewFile(DWORD Size, LPCVOID Buffer);
	BOOL WriteMemoryToFile(LONG Offset, DWORD Size, LPCVOID Buffer);
	BOOL WriteZeroMemoryToFile(LONG Offset, DWORD Size);
};

