#include "MemorySourceExport.h"

#include <algorithm>

#include "ProcessMemory.hpp"

auto GetMemorySourcesExport(MemorySources * memory_sources) -> VOID
{
	//
	// Copy the memory sources to the buffer
	//
	auto i = 0;
	for (auto & memory_source : MemorySource::GetMemorySources())
	{
		//
		// Add a string to set the end
		//
		memory_source.append("|");

		//
		// Create the char array
		//
		memory_sources->memory_sources[i] = new char[memory_source.length()];

		//
		// Clear the memory
		//
		RtlSecureZeroMemory(memory_sources->memory_sources[i], memory_source.length());

		//
		// Copy the string
		//
		std::copy(memory_source.begin(), memory_source.end(), memory_sources->memory_sources[i++]);
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
