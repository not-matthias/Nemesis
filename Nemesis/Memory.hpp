#pragma once

#include "ProcessMemory.hpp"

class Memory
{
	ProcessMemory *process_memory;

public:
	DWORD_PTR start_address;
	DWORD memory_size;
	BYTE *memory_buffer;

	Memory(ProcessMemory *process_memory, DWORD_PTR start_address, DWORD size);
	~Memory();

	auto Initialize() -> BOOL;
};

