#include "MemorySourceExport.h"
#include "ProcessMemory.hpp"

auto GetMemorySources() -> std::vector<std::string>
{
	// TODO: Convert to PCHAR[]
	return MemorySource::GetMemorySources();
}

auto SetMemorySource(const char * memory_source_name) -> VOID
{
	MemorySource::SetMemorySource(memory_source_name);
}
