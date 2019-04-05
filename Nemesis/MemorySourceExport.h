#pragma once

#include <vector>
#include <Windows.h>
#include <string>

/**
 * \brief Returns a list of memory sources.
 * \return the list
 */
auto GetMemorySources() ->std::vector<std::string>;

/**
 * \brief Sets the new memory source.
 * \param memory_source_name the specified memory source
 */
auto SetMemorySource(const char * memory_source_name) -> VOID;
