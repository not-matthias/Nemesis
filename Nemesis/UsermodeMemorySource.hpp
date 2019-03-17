#pragma once

#include "IMemorySource.hpp"
#include "Logger.hpp"

class UsermodeMemorySource: public IMemorySource
{
private:
	HANDLE hProcess = NULL;

public:
	UsermodeMemorySource(DWORD Pid);
	~UsermodeMemorySource();

	BOOL ReadMemory(DWORD_PTR StartAddress, DWORD_PTR EndAddress);
};

