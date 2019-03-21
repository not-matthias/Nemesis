#pragma once

#include "IMemorySource.hpp"
#include "Logger.hpp"

#include <iostream>
#include <Psapi.h>
#include <string>
#include <Windows.h>

class UsermodeMemory : public IMemorySource
{
private:
	HANDLE hProcess = NULL;

public:
	UsermodeMemory(DWORD Pid);
	~UsermodeMemory();

	PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size);
	DWORD_PTR GetBaseAddress();
};
