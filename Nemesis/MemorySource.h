#pragma once

#include <memory>
#include <string>
#include <vector>

#include "IMemorySource.hpp"

class MemorySource
{
	/**
	 * \brief All the memory sources.
	 */
	static std::vector<std::string> memory_sources;

public:
	//
	//
	// Important functions
	//
	//

	/**
	 * \brief Returns the memory source.
	 * \param process_id the id of the process
	 * \return the memory source the memory source
	 */
	static auto GetMemorySource(DWORD process_id) -> std::shared_ptr<IMemorySource>;

	/**
	 * \brief Returns all memory sources.
	 * \return the memory sources
	 */
	static auto GetMemorySources() -> std::vector<std::string>;
};
