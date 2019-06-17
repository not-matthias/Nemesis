#pragma once

#include <Windows.h>

#include "MemorySource.h"

class ProcessMemory
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The id of the process.
	 */
	DWORD process_id;


public:

	//
	//
	// Constructor
	//
	//

	/**
	 * \brief Stores the parameters.
	 * \param process_id the id of the process
	 */
	ProcessMemory(DWORD process_id);


	//
	//
	// Important functions
	//
	//

	/**
	  * \brief Reads memory from the process. (e.g. float)
	 * \tparam T the read value data type
	 * \param start_address the memory start address
	 * \return the memory buffer
	 */
	template <typename T>
	auto ReadMemory(const DWORD_PTR start_address) -> T
	{
		return reinterpret_cast<T>(MemorySource::GetMemorySource(process_id)->ReadMemory(start_address, sizeof(T)));
	}

	/**
	 * \brief Reads memory from the process. (e.g. float or float[])
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) const -> std::shared_ptr<BYTE>;


	//
	//
	// Checks
	//
	//

	/**
	 * \brief Checks whether the memory is valid.
	 * \return true if successful
	 */
	auto IsValid() const -> BOOL;


	//
	//
	// Getters
	//
	//

	/**
	 * \brief Returns the base address.
	 * \return the base address of the process
	 */
	auto GetBaseAddress() const -> DWORD_PTR;

	/**
	 * \brief Returns the process id.
	 * \return the id of the process
	 */
	auto GetProcessId() const -> DWORD;
};
