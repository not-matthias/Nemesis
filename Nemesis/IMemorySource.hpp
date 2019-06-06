#pragma once

#include <Windows.h>

class IMemorySource
{
protected:
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The process id.
	 */
	DWORD process_id;

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
	explicit IMemorySource(DWORD process_id);

	/**
	 * \brief Frees the resources.
	 */
	virtual ~IMemorySource() = default;


	//
	//
	// Important functions
	//
	//

	/**
	 * \brief Reads the memory from the process.
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	virtual auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> std::shared_ptr<BYTE *> = 0;


	//
	//
	// Checks
	//
	//

	/**
	 * \brief Checks whether the memory source is valid.
	 * \return true if valid
	 */
	virtual auto IsValid() -> BOOL = 0;


	//
	//
	// Getters
	//
	//

	/**
	 * \brief Returns the base address.
	 * \return the base address of the process
	 */
	virtual auto GetBaseAddress() -> DWORD_PTR = 0;
};
