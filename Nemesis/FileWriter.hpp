#pragma once

#include <string>

#include "Memory.hpp"
#include "Module.hpp"
#include "SmartHandle.hpp"

class FileWriter
{
	/**
	 * \brief The name of the exported file.
	 */
	std::wstring file_name;

	/**
	 * \brief The handle to the file.
	 */
	SmartHandle file_handle = nullptr;

public:

	/**
	 * \brief Stores the parameter.
	 * \param file_name the name of the dump file
	 */
	explicit FileWriter(std::wstring file_name);

	/**
	 * \brief Writes the module to the file.
	 * \param module the module to dumped
	 * \return true if successful
	 */
	auto WriteToFile(Module * module) -> BOOL;

	/**
	 * \brief Writes the memory to the file.
	 * \param memory the memory to dump
	 * \return true if successful
	 */
	auto WriteToFile(MemoryElement * memory) -> BOOL;

	/**
	 * \brief Writes the specified buffer to the file.
	 * \param offset the file offset
	 * \param size the buffer size
	 * \param buffer 
	 * \return true if successful
	 */
	auto WriteMemoryToFile(LONG offset, DWORD size, std::shared_ptr<BYTE> buffer) const -> BOOL;

	/**
	 * \brief Writes zero memory to the file.
	 * \param offset 
	 * \param size 
	 * \return true if successful
	 */
	auto WriteZeroMemoryToFile(LONG offset, DWORD size) const -> BOOL;
};
