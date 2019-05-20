#pragma once

#include <Windows.h>

/**
 * \brief Dumps the main Module (e.g. process.exe).
 * \param process_id the id of the process
 * \param file_name the dump file name
 * \return true if successful
 */
auto DumpProcessExport(DWORD process_id, LPCSTR file_name) -> BOOL;

/**
 * \brief Dumps a specific Module (e.g. kernel32.dll).
 * \param process_id the id of the process
 * \param base_address the base address of the module
 * \param file_name the dump file name
 * \return true if successful
 */
auto DumpModuleExport(DWORD process_id, DWORD_PTR base_address, LPCSTR file_name) -> BOOL;

/**
 * \brief Dumps a specific memory region.
 * \param process_id the id of the process
 * \param start_address the starting address of the memory region
 * \param size the size of the memory region
 * \param file_name the dump file name
 * \return true if successful
 */
auto DumpMemoryExport(DWORD process_id, DWORD_PTR start_address, DWORD size, LPCSTR file_name) -> BOOL;

/**
 * \brief Dumps a specific drier.
 * \param base_address the base address of the driver
 * \param file_name the dump file name
 * \return true if successful
 */
auto DumpDriverExport(DWORD_PTR base_address, LPCSTR file_name) -> BOOL;
