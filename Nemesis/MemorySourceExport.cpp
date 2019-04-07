#include "MemorySourceExport.h"

#include <algorithm>

#include "ProcessMemory.hpp"

auto GetMemorySourcesExport(PVOID const buffer) -> VOID
{
	//
	// Cast the buffer
	//
	auto memory_sources = static_cast<MemorySources *>(buffer);

	//
	// Copy the memory sources to the buffer
	//
	auto i = 0;
	for (const auto & memory_source : MemorySource::GetMemorySources())
	{
		strcpy_s(memory_sources->memory_sources[i++], sizeof(memory_source.data()), memory_source.data());
	}
}

auto SetMemorySourceExport(const char * memory_source_name) -> BOOL
{
	auto memory_sources = MemorySource::GetMemorySources();

	//
	// Check if memory source exists
	//
	if (std::find(memory_sources.begin(), memory_sources.end(), memory_source_name) != memory_sources.end())
	{
		return FALSE;
	}

	//
	// Memory source does exist
	//
	MemorySource::SetMemorySource(memory_source_name);

	return TRUE;
}
