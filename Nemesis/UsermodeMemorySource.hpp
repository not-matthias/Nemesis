#pragma once

#include "IMemorySource.hpp"
#include "Logger.hpp"
#include <Psapi.h>
#include <string>
#include <Windows.h>

class UsermodeMemorySource : public IMemorySource
{
private:
	HANDLE hProcess = NULL;

public:
	UsermodeMemorySource(DWORD Pid);
	~UsermodeMemorySource();

	PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size);
	DWORD_PTR GetBaseAddress();
};
