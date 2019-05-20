#pragma once

#include <Windows.h>


/**
 * \brief A memory region of a process.
 */
struct Memory
{
	PVOID base_address;
	SIZE_T region_size;
	DWORD state;
	DWORD type;
};

/**
 * \brief A module of a process.
 */
struct Module
{
	CHAR module_name[MAX_PATH];
	INT64 base_address;
};

/**
 * \brief Contains all the information about a process.
 */
struct Process
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
	Process * processes;
};


/**
 * \brief Returns the process at the specified index. 
 * \param index the index in the list
 * \param process the process at the specified index
 * \return true if successful
 */
auto GetProcessListElementExport(IN UINT index, OUT Process * process) -> BOOL;

/**
 * \brief Returns the module at the specified index.
 * \param index the index in the list
 * \param process_id the id of the process
 * \param module the module at the specified index
 * \return true if successful
 */
auto GetModuleListElementExport(IN UINT index, IN DWORD process_id, OUT Module * module) -> BOOL;

/**
 * \brief Returns the memory at the specified index.
 * \param index the index in the list
 * \param process_id the id of the process
 * \param memory the memory at the specified index
 * \return true if successful
 */
auto GetMemoryListElementExport(IN UINT index, IN DWORD process_id, OUT Memory * memory) -> BOOL;
