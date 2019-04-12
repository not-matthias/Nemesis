#pragma once

#include <Windows.h>

struct Section
{
};

struct Memory
{
	PVOID base_address;
	SIZE_T region_size;
	DWORD state;
	DWORD type;
};

struct Module
{
	CHAR module_name[MAX_PATH];
	INT64 base_address;
};

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

struct Process
{
	ProcessInformation process_information;

	Module modules[32];
	Section sections[32];
	Memory memory_regions[64];
};

struct ProcessList
{
	Process processes[256];
};

auto GetProcessListExport(ProcessList * process_list) -> VOID;

// NtQueryVirtualMemory
// https://stackoverflow.com/questions/46978645/how-list-all-modules-of-system-not-modules-of-my-own-process