#include "stdafx.h"

#include "Logger.hpp"
#include "Memory.hpp"

MemoryElement::MemoryElement(ProcessMemory * process_memory, const DWORD_PTR start_address, const DWORD size)
{
	this->memory_buffer = nullptr;
	this->process_memory = process_memory;
	this->start_address = start_address;
	this->memory_size = size;
}

MemoryElement::~MemoryElement()
{
	delete memory_buffer;
}

auto MemoryElement::Initialize() -> BOOL
{
	Logger::Log("Initializing the memory.");

	//
	// Get the Memory
	//
	memory_buffer = process_memory->ReadMemory<BYTE*>(start_address, memory_size);

	//
	// Check if valid
	//
	if (memory_buffer == nullptr)
	{
		return FALSE;
	}

	return TRUE;
}
