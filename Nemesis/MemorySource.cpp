#include "MemorySource.h"

#include "UsermodeMemory.hpp"
#include "KernelMemory.hpp"

std::string MemorySource::current_memory_source;
std::vector<std::string> MemorySource::memory_sources;;


MemorySource::MemorySource()
{
	memory_sources.emplace_back("user_mode");
	memory_sources.emplace_back("kernel_mode");
}

MemorySource::~MemorySource() = default;

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
	if (current_memory_source == "kernel_mode")
	{
		return new KernelMemory(process_id);
	}

	//
	// Default: Usermode memory
	//
	return new UsermodeMemory(process_id);
}

auto MemorySource::GetMemorySources() -> std::vector<std::string>
{
	return memory_sources;
}
