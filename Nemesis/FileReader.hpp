#pragma once

#include <string>
#include <Windows.h>

#include "SafeHandle.hpp"

class FileReader
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The path to the file.
	 */
	std::wstring path;

	/**
	 * \brief The handle to the file.
	 */
	SafeHandle file_handle = nullptr;

public:

	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Stores the parameter.
	 * \param path the path of the file
	 */
	explicit FileReader(std::wstring path);

	/**
	 * \brief The default destructor.
	 */
	~FileReader();


	//
	//
	// Functions
	//
	//

	/**
	 * \brief Reads from a file.
	 * \param offset the file offset
	 * \param size the buffer size
	 * \return the buffer
	 */
	auto Read(LONG offset, DWORD size) -> std::shared_ptr<BYTE>;
};
