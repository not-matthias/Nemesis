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

		std::copy(image_name.begin(), image_name.end(), process.process_information.image_name);
		process.process_information.unique_process_id = system_process_info->UniqueProcessId;
		process.process_information.number_of_threads = system_process_info->NumberOfThreads;
		process.process_information.base_priority = system_process_info->BasePriority;
		process.process_information.handle_count = system_process_info->HandleCount;
		process.process_information.session_id = system_process_info->SessionId;
		process.process_information.peak_virtual_size = system_process_info->PeakVirtualSize;
		process.process_information.virtual_size = system_process_info->VirtualSize;
		process.process_information.peak_working_set_size = system_process_info->PeakWorkingSetSize;
		process.process_information.working_set_size = system_process_info->WorkingSetSize;
		process.process_information.quota_paged_pool_usage = system_process_info->QuotaPagedPoolUsage;
		process.process_information.quota_non_paged_pool_usage = system_process_info->QuotaNonPagedPoolUsage;
		process.process_information.page_file_usage = system_process_info->PagefileUsage;
		process.process_information.peak_page_file_usage = system_process_info->PeakPagefileUsage;
		process.process_information.private_page_count = system_process_info->PrivatePageCount;

		// TODO: Get base address

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

auto ProcessUtils::GetModuleList() -> void
{

}
