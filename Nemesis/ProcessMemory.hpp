#pragma once

#include "IMemorySource.hpp"
#include "UsermodeMemorySource.hpp"

#include <iostream>
#include <vector>
#include <Windows.h>

class ProcessMemory
{
private:
	DWORD Pid;
	IMemorySource *pMemorySource = nullptr;

	// TODO: Add list of memory sources here

public:
	ProcessMemory(DWORD Pid);
	~ProcessMemory();

	template <typename T> 
	T ReadMemory(DWORD_PTR StartAddress);

	PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size);

	DWORD_PTR GetBaseAddress();
};
