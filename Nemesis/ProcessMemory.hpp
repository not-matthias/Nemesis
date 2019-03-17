#pragma once

#include "IMemorySource.hpp"
#include "UsermodeMemorySource.hpp"

#include <iostream>
#include <vector>
#include <Windows.h>

class Memory
{
private:
	DWORD Pid;
	IMemorySource *pMemorySource = nullptr;

	// TODO: Add list of memory sources here

public:
	Memory(DWORD Pid);
	~Memory();

	BOOL ReadMemory(DWORD_PTR StartAddress, DWORD_PTR EndAddress);
	// TODO: Read Headers
};

