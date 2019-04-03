#pragma once

#include "IMemorySource.hpp"
#include <Windows.h>

class ProcessMemory
{
	DWORD process_id;
	IMemorySource *memory_source = nullptr;

	// TODO: Add list of Memory sources here

public:
	explicit ProcessMemory(DWORD process_id);
	~ProcessMemory();

	//
	// Functions
	//
	template <typename T>
	auto ReadMemory(DWORD_PTR start_address) -> T;

	PVOID ReadMemory(DWORD_PTR start_address, SIZE_T size) const;

	//
	// Getters
	//
	auto GetBaseAddress() const -> DWORD_PTR;

	//
	// Checks
	//
	auto IsValid() const -> BOOL;
};
