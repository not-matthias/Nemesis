#include "stdafx.h"

#include "KernelMemory.hpp"
#include "MemorySource.h"
#include "UsermodeMemory.hpp"

std::string MemorySource::current_memory_source;
std::vector<std::string> MemorySource::memory_sources = {"kernel_mode", "user_mode"};

auto MemorySource::SetMemorySource(const std::string & memory_source_name) -> VOID
{
	current_memory_source = memory_source_name;
}

auto MemorySource::GetMemorySource(const DWORD process_id) -> std::shared_ptr<IMemorySource>
{
	// 
	// Kernel Memory
	// 
	if (current_memory_source.find("kernel_mode") != std::string::npos)
	{
		return std::static_pointer_cast<IMemorySource>(std::make_shared<KernelMemory>(process_id));
	}

	//
	// Default: Usermode memory
	//
	return std::static_pointer_cast<IMemorySource>(std::make_shared<UsermodeMemory>(process_id));
}

auto MemorySource::GetMemorySources() -> std::vector<std::string>
{
	return memory_sources;
}
