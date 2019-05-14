#include "MemorySource.h"

#include "UsermodeMemory.hpp"
#include "KernelMemory.hpp"
#include <ostream>
#include <iostream>

std::string MemorySource::current_memory_source;
std::vector<std::string> MemorySource::memory_sources = {"kernel_mode", "user_mode"};

auto MemorySource::SetMemorySource(const std::string & memory_source_name) -> VOID
{
	// TODO: Check if it exists
	current_memory_source = memory_source_name;
}

auto MemorySource::GetMemorySource(const DWORD process_id) -> IMemorySource *
{
	// 
	// Kernel Memory
	// 
	if (current_memory_source.compare("kernel_mode"))
	{
		// TODO: Leaking memory here
		return new KernelMemory(process_id);
	}

	//
	// Default: Usermode memory
	//
	// TODO: Leaking memory here
	return new UsermodeMemory(process_id);
}

auto MemorySource::GetMemorySources() -> std::vector<std::string>
{
	return memory_sources;
}
