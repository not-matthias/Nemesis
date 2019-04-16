#pragma once

#include <Windows.h>

// TODO: Add sections (from the pe header)
/**
 * \brief A section of a process.
 */
struct Section
{
};

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
 * \brief The information about a process.
 */
struct ProcessInformation
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
 * \brief Contains all the information about a process.
 */
struct Process
{
	ProcessInformation process_information;
};

/**
 * \brief Contains the list of processes.
 */
struct ProcessList
{
	Process * processes;
};


/**
 * \brief Creates a new process list.
 * \param process_list the output buffer
 */
auto GetProcessListExport(OUT ProcessList * process_list) -> VOID;
