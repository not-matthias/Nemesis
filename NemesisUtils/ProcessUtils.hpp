#pragma once

#include "ProcessExport.hpp"

#pragma comment(lib,"ntdll.lib")

class ProcessUtils
{
public:
	/**
	 * \brief Creates the process list struct.
	 * \return the structure
	 */
	static auto GetProcessList() -> ProcessList*;

	/**
	 * \brief Creates the module array.
	 * \param process_id the target process id
	 * \return the module array
	 */
	static auto GetModuleList(DWORD process_id) -> Module*;

	/**
	 * \brief Creates the memory regions array.
	 * \param process_id the target process id
	 * \return the memory array
	 */
	static auto GetMemoryRegions(DWORD process_id) -> Memory*;
};
