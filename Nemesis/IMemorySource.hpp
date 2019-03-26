#pragma once

#include <Windows.h>

// 1. Implement the interface
// 2. Implement the methods
// 3. Add and switch to the MemorySource to the list in the Memory class


class IMemorySource 
{
protected:
	DWORD Pid;

public:
	IMemorySource(DWORD Pid);

	virtual PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size) = 0;

	virtual DWORD_PTR GetBaseAddress() = 0;
};