#include "MemorySourceExport.h"
#include "ProcessMemory.hpp"

auto GetMemorySources() -> const char **
{
	return ProcessMemory::GetMemorySources().data();
}

auto SetMemorySource(char * memory_source_name) -> VOID
{
	ProcessMemory::SetMemorySource(memory_source_name);
}
