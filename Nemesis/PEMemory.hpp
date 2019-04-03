#pragma once

#include "ProcessMemory.hpp"

class Memory
{
private:
	ProcessMemory *pProcessMemory;

public:
	DWORD_PTR StartAddress;
	DWORD Size;
	PVOID Buffer;

	Memory(ProcessMemory *pProcessMemory, DWORD_PTR StartAddress, DWORD Size);
	~Memory();

	BOOL Initialize();
};

