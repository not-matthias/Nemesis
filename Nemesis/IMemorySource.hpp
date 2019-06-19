#pragma once

#include <Windows.h>

class IMemorySource
{
protected:

	/**
	 * \brief The process id.
	 */
	DWORD process_id;

public:

	/**
	 * \brief Stores the parameters.
	 * \param process_id the id of the process
	 */
	explicit IMemorySource(DWORD process_id);

	/**
	 * \brief Reads the memory from the process.
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	virtual auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> std::shared_ptr<BYTE> = 0;
	
	/**
	 * \brief Checks whether the memory source is valid.
	 * \return true if valid
	 */
	virtual auto IsValid() -> BOOL = 0;

	/**
	 * \brief Returns the base address.
	 * \return the base address of the process
	 */
	virtual auto GetBaseAddress() -> DWORD_PTR = 0;
};
