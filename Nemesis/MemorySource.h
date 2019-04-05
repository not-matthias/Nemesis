#pragma once

#include <vector>
#include <string>

#include "IMemorySource.hpp"

class MemorySource
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The current memory source.
	 */
	static std::string current_memory_source;

public:

	/**
	 * \brief All the memory sources.
	 */
	static std::vector<std::string> memory_sources;


	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Adds the memory sources to the list.
	 */
	MemorySource();

	/**
	 * \brief Default destructor.
	 */
	~MemorySource();


	//
	//
	// Important functions
	//
	//

	/**
	 * \brief Set the new current memory source.
	 * \param memory_source_name the new memory source
	 */
	static auto SetMemorySource(const std::string & memory_source_name) -> VOID;

	/**
	 * \brief Returns the memory source.
	 * \param process_id the id of the process
	 * \return the memory source the memory source
	 */
	static auto GetMemorySource(DWORD process_id) -> IMemorySource*;

	/**
	 * \brief Returns all memory sources.
	 * \return the memory sources
	 */
	static auto GetMemorySources() -> std::vector<std::string>;
};
