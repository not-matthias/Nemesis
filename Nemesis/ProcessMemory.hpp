#pragma once

#include "IMemorySource.hpp"
#include <Windows.h>

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

	/**
	 * \brief The process memory wrapper.
	 */
	IMemorySource * memory_source = nullptr;

	// TODO: Add list of Memory sources here


public:

	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Stores the parameters.
	 * \param process_id the id of the process
	 */
	explicit ProcessMemory(DWORD process_id);

	/**
	 * \brief Deletes the memory source.
	 */
	~ProcessMemory();

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
	auto ReadMemory(DWORD_PTR start_address) -> T;

	/**
	 * \brief Reads memory from the process. (e.g. float[])
	 * \tparam T the read value data type
	 * \param start_address the memory start address
	 * \param size the size of the memory buffer
	 * \return the memory buffer
	 */
	template <typename T>
	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> T;

	/**
	 * \brief Reads memory from the process. (e.g. float or float[])
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) const -> PVOID;


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
};
