#pragma once

#include <vector>
#include <Windows.h>

/**
 * \brief Returns a list of memory sources.
 * \return the list
 */
auto GetMemorySources() -> const char **;

/**
 * \brief Sets the new memory source.
 * \param memory_source_name the specified memory source
 */
auto SetMemorySource(char * memory_source_name) -> VOID;
