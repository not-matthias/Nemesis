#include "stdafx.h"

#include "Logger.hpp"
#include "Memory.hpp"

MemoryElement::MemoryElement(ProcessMemory * process_memory, const DWORD_PTR start_address, const DWORD size) : process_memory(process_memory),
                                                                                                                start_address(start_address),
                                                                                                                memory_size(memory_size)
{
}

auto MemoryElement::Initialize() -> BOOL
{
	Logger::Log("Initializing the memory.");

	//
	// Get the Memory
	//
	memory_buffer = process_memory->ReadMemory(start_address, memory_size);

	//
	// Check if valid
	//
	if (memory_buffer == nullptr)
	{
		return FALSE;
	}

	return TRUE;
}
