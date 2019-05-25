#pragma once

#include "ProcessExport.hpp"

#include <string>
#include <vector>

#pragma comment(lib,"ntdll.lib")

class ProcessUtils
{
public:
	/**
	 * \brief Creates the process list struct.
	 * \return the structure
	 */
	static auto GetProcessList() -> std::vector<ProcessElement>;

	/**
	 * \brief Creates the module array.
	 * \param process_id the target process id
	 * \return the module array
	 */
	static auto GetModuleList(DWORD process_id) -> std::vector<ModuleElement>;

	/**
	 * \brief Creates the memory regions array.
	 * \param process_id the target process id
	 * \return the memory array
	 */
	static auto GetMemoryList(DWORD process_id) -> std::vector<MemoryElement>;

	/**
	 * \brief Returns the path of the process' main module.
	 * \param process_id the target process id
	 * \return the path to the main module
	 */
	static auto GetFilePath(DWORD process_id) -> std::string;
};
