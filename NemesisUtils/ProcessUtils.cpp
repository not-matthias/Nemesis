#include "ProcessUtils.hpp"
#include <iostream>
#include <winternl.h>

auto ProcessUtils::GetProcessList() -> ProcessList*
{
	auto process_list = new ProcessList[256];

	//
	// Allocate memory for the buffer
	//
	LPVOID buffer = nullptr;
	if (!(buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)))
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		return process_list;
	}

	//
	// Create the process info buffer
	//
	auto system_process_info = static_cast<PSYSTEM_PROCESS_INFORMATION>(buffer);

	//
	// Get the process list
	//
	if (!NT_SUCCESS(NtQuerySystemInformation(SystemProcessInformation, system_process_info, 1024 * 1024, NULL)))
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		return process_list;
	}

	//
	// Create the process list
	//
	auto index = 0;
	while (system_process_info->NextEntryOffset)
	{
		//
		// Create the process struct
		//
		std::wstring image_name{system_process_info->ImageName.Buffer, static_cast<UINT64>(system_process_info->ImageName.Length / 2)};

		Process process{};

		std::copy(image_name.begin(), image_name.end(), process.image_name);
		process.unique_process_id = system_process_info->UniqueProcessId;
		process.number_of_threads = system_process_info->NumberOfThreads;
		process.base_priority = system_process_info->BasePriority;
		process.handle_count = system_process_info->HandleCount;
		process.session_id = system_process_info->SessionId;
		process.peak_virtual_size = system_process_info->PeakVirtualSize;
		process.virtual_size = system_process_info->VirtualSize;
		process.peak_working_set_size = system_process_info->PeakWorkingSetSize;
		process.working_set_size = system_process_info->WorkingSetSize;
		process.quota_paged_pool_usage = system_process_info->QuotaPagedPoolUsage;
		process.quota_non_paged_pool_usage = system_process_info->QuotaNonPagedPoolUsage;
		process.page_file_usage = system_process_info->PagefileUsage;
		process.peak_page_file_usage = system_process_info->PeakPagefileUsage;
		process.private_page_count = system_process_info->PrivatePageCount;

		//
		// Add the process to the list
		//
		process_list->processes[index++] = process;

		//
		// Calculate the next offset
		//
		system_process_info = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(reinterpret_cast<LPBYTE>(system_process_info) +
			system_process_info->NextEntryOffset);
	}

	// 
	// Free the buffer
	// 
	VirtualFree(buffer, 0, MEM_RELEASE);

	//
	// Return the list
	//
	return process_list;
}
