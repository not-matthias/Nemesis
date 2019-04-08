#pragma once

#include <string>
#include <vector>
#include <Windows.h>

/**
 * \brief Contains the memory sources.
 */
struct MemorySources
{
	char * memory_sources[12];
};


/**
 * \brief Returns a list of memory sources.
 * \return the list of memory sources
 */
auto GetMemorySourcesExport(OUT MemorySources * memory_sources) -> VOID;

/**
 * \brief Sets the new memory source.
 * \param memory_source_name the specified memory source
 * \return true if successful
 */
auto SetMemorySourceExport(IN const char * memory_source_name) -> BOOL;
