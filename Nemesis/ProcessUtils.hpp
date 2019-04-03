#pragma once

#include <vector>
#include <Windows.h>
#include <winternl.h>

#pragma comment(lib,"ntdll.lib")

typedef struct _SYSTEM_PROCESS_INFO
{
	ULONG                   next_entry_offset;
	ULONG                   number_of_threads;
	LARGE_INTEGER           reserved[3];
	LARGE_INTEGER           create_time;
	LARGE_INTEGER           user_time;
	LARGE_INTEGER           kernel_time;
	UNICODE_STRING          image_name;
	ULONG                   base_priority;
	HANDLE                  process_id;
	HANDLE                  inherited_from_process_id;
}SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;

struct PROCESS
{
	HANDLE					process_id;
	UNICODE_STRING			image_name;
};

auto GetProcessList() -> std::vector<PROCESS *>;
