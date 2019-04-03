#include "Memory.hpp"

Memory::Memory(ProcessMemory * process_memory, const DWORD_PTR start_address, const DWORD size)
{
	this->memory_buffer = nullptr;
	this->process_memory = process_memory;
	this->start_address = start_address;
	this->memory_size = size;
}

Memory::~Memory()
{
	delete memory_buffer;
}

auto Memory::Initialize() -> BOOL
{
	//
	// Get the Memory
	//
	memory_buffer = static_cast<BYTE *>(process_memory->ReadMemory(start_address, memory_size));

	//
	// Check if valid
	//
	if (memory_buffer == nullptr)
	{
		return FALSE;
	}

	return TRUE;
}
