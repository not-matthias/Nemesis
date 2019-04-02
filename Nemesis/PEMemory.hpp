#pragma once

#include "ProcessMemory.hpp"

class PEMemory
{
private:
	ProcessMemory *pProcessMemory;

public:
	DWORD_PTR StartAddress;
	DWORD Size;
	PVOID Buffer;

	PEMemory(ProcessMemory *pProcessMemory, DWORD_PTR StartAddress, DWORD Size);
	~PEMemory();

	BOOL Initialize();
};

