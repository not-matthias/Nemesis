#pragma once

#include "IMemorySource.h"

class MemorySource : public IMemorySource
{
public:
	MemorySource();
	~MemorySource();

	void ReadMemory(DWORD Pid, DWORD_PTR StartAddress, DWORD_PTR EndAddress);
};

