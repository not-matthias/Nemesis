#include "MemorySourceExport.h"
#include "ProcessMemory.hpp"

auto GetMemorySources() -> std::vector<const char *>
{
	return ProcessMemory::GetMemorySources();
}

auto SetMemorySource(char * memory_source_name) -> VOID
{
	ProcessMemory::SetMemorySource(memory_source_name);
}
