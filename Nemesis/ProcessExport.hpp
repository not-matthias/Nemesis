#pragma once

#include <Windows.h>

/**
 * \brief A memory region of a process.
 */
struct MemoryElement
{
	PVOID base_address;
	SIZE_T region_size;
	DWORD state;
	DWORD type;
};

/**
 * \brief A module of a process.
 */
struct ModuleElement
{
	PVOID base_address;
	SIZE_T module_size;
	CHAR module_name[MAX_PATH];
	CHAR module_path[MAX_PATH];
};

/**
 * \brief Contains all the information about a process.
 */
struct ProcessElement
{
	CHAR image_name[256];
	HANDLE unique_process_id;
	INT32 number_of_threads;
	INT32 base_priority;
	INT32 handle_count;
	INT32 session_id;
	SIZE_T peak_virtual_size;
	SIZE_T virtual_size;
	SIZE_T peak_working_set_size;
	SIZE_T working_set_size;
	SIZE_T quota_paged_pool_usage;
	SIZE_T quota_non_paged_pool_usage;
	SIZE_T page_file_usage;
	SIZE_T peak_page_file_usage;
	SIZE_T private_page_count;
};

/**
 * \brief Contains the list of processes.
 */
struct ProcessList
{
	ProcessElement * processes;
};


/**
 * \brief Returns the process at the specified index. 
 * \param index the index in the list
 * \param process the process at the specified index
 * \return true if successful
 */
auto GetProcessListElementExport(IN UINT index, OUT ProcessElement * process) -> BOOL;

/**
 * \brief Returns the module at the specified index.
 * \param index the index in the list
 * \param process_id the id of the process
 * \param module the module at the specified index
 * \return true if successful
 */
auto GetModuleListElementExport(IN UINT index, IN DWORD process_id, OUT ModuleElement * module) -> BOOL;

/**
 * \brief Returns the manually enumerated module at the specified index.
 * \param index the index in the list
 * \param process_id the id of the process
 * \param module the module at the specified index
 * \return true if successful
 */
auto GetManualModuleListElementExport(IN UINT index, IN DWORD process_id, OUT ModuleElement * module) -> BOOL;

/**
 * \brief Returns the memory at the specified index.
 * \param index the index in the list
 * \param process_id the id of the process
 * \param memory the memory at the specified index
 * \return true if successful
 */
auto GetMemoryListElementExport(IN UINT index, IN DWORD process_id, OUT MemoryElement * memory) -> BOOL;
