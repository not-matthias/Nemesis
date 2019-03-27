#pragma once

#include "IMemorySource.hpp"
#include "UsermodeMemory.hpp"

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

	//
	// Functions
	//
	template <typename T> 
	T ReadMemory(DWORD_PTR StartAddress);

	PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size);

	//
	// Getters
	//
	DWORD_PTR GetBaseAddress();

	//
	// Checks
	//
	BOOL IsValid();
};
