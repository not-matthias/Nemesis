#pragma once

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
