#pragma once

#include <Windows.h>

struct Section
{
};

struct Memory
{
};

struct Module
{
};

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

struct ProcessList
{
	Process processes[256];
};

auto GetProcessListExport(ProcessList * process_list) -> VOID;
