#pragma once

#include "ProcessMemory.hpp"

class MemoryElement
{
	/**
	 * \brief The process memory wrapper.
	 */
	ProcessMemory * process_memory;

public:

	/**
	 * \brief The memory start address.
	 */
	DWORD_PTR start_address;

	/**
	 * \brief The memory size.
	 */
	DWORD memory_size;

	/**
	 * \brief The memory buffer.
	 */
	std::shared_ptr<BYTE> memory_buffer;


	/**
	 * \brief Stores the parameters.
	 * \param process_memory the process memory wrapper
	 * \param start_address the memory start address
	 * \param size the memory size
	 */
	MemoryElement(ProcessMemory * process_memory, DWORD_PTR start_address, DWORD size);

	/**
	 * \brief Reads the memory and stores it in the memory_buffer.
	 * \return true if successful
	 */
	auto Initialize() -> BOOL;
};
