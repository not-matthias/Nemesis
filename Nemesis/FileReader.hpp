#pragma once

#include <string>
#include <Windows.h>

#include "SmartHandle.hpp"

class FileReader
{
	/**
	 * \brief The path to the file.
	 */
	std::wstring path;

	/**
	 * \brief The handle to the file.
	 */
	SmartHandle file_handle = nullptr;

public:

	/**
	 * \brief Stores the parameter.
	 * \param path the path of the file
	 */
	explicit FileReader(std::wstring path);

	/**
	 * \brief Reads from a file.
	 * \param offset the file offset
	 * \param size the buffer size
	 * \return the buffer
	 */
	auto Read(LONG offset, DWORD size) -> std::shared_ptr<BYTE>;
};
