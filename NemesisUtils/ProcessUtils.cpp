#include "ProcessUtils.hpp"

#include <iostream>
#include <Psapi.h>
#include <vector>
#include <winternl.h>

auto ProcessUtils::GetProcessList() -> ProcessList*
{
	auto process_list = new ProcessList;
	std::vector<Process> processes;

	//
	// Allocate memory for the buffer
	//
	LPVOID buffer = nullptr;
	if (!(buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE)))
	{
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
		std::string string(image_name.begin(), image_name.end());
		Process process{};

		std::copy(string.begin(), string.end(), reinterpret_cast<char*>(process.process_information.image_name));
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
		// Set the modules
		//
		process.modules = GetModuleList(reinterpret_cast<DWORD>(system_process_info->UniqueProcessId));

		//
		// Set the memory regions 
		//
		process.memory_regions = GetMemoryRegions(reinterpret_cast<DWORD>(system_process_info->UniqueProcessId));

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

auto ProcessUtils::GetModuleList(const DWORD process_id) -> Module*
{
	std::vector<Module> modules;

	HMODULE module_handles[1024];
	DWORD cb_needed;

	//
	// Open the process
	//
	const auto process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	//
	// Loop through the modules
	//
	if (EnumProcessModules(process_handle, module_handles, sizeof(module_handles), &cb_needed))
	{
		for (unsigned long i = 0; i < (cb_needed / sizeof(HMODULE)); i++)
		{
			CHAR module_name[MAX_PATH];

			//
			// Get the full path
			//
			if (GetModuleFileNameEx(process_handle, module_handles[i], module_name, sizeof(module_name) / sizeof(CHAR)))
			{
				std::cout << "[" << process_id << "]" << module_name << std::endl;

				//
				// Create a new module
				//
				Module module{};

				std::string module_name_string(module_name);
				std::copy(module_name_string.begin(), module_name_string.end(), reinterpret_cast<char *>(module.module_name));
				module.base_address = reinterpret_cast<INT64>(module_handles[i]);

				//
				// Add it to the list
				//
				modules.push_back(module);
			}
		}
	}

	//
	// Close the handle
	//
	CloseHandle(process_handle);

	std::cout << modules.size() << std::endl;

	//
	// Create a copy of the list and return it
	//
	const auto module_list = new Module[modules.size()];
	std::copy(modules.begin(), modules.end(), module_list);

	//return module_list;
	return modules.data();
}

auto ProcessUtils::GetMemoryRegions(const DWORD process_id) -> Memory*
{
	std::vector<Memory> memory_list;

	//
	// Open the process
	//
	const auto process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, process_id);
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	MEMORY_BASIC_INFORMATION memory_basic_information;

	// 
	// Loop through the memory regions
	// 
	for (BYTE * memory_region_start = nullptr;
	     VirtualQueryEx(process_handle, memory_region_start, &memory_basic_information, sizeof(MEMORY_BASIC_INFORMATION));
	     memory_region_start += memory_basic_information.RegionSize)
	{
		//
		// Creates a new memory source
		//
		Memory memory{};
		memory.base_address = memory_basic_information.BaseAddress;
		memory.region_size = memory_basic_information.RegionSize;
		memory.state = memory_basic_information.State; // (MEM_COMMIT | MEM_FREE | MEM_RESERVE)
		memory.type = memory_basic_information.Type; // (MEM_IMAGE | MEM_MAPPED | MEM_PRIVATE)

		//
		// Add it to the list
		//
		memory_list.push_back(memory);
	}

	//
	// Close the handle
	//
	CloseHandle(process_handle);

	//
	// Create a copy of the list and return it
	//
	const auto memory_regions = new Memory[memory_list.size()];
	std::copy(memory_list.begin(), memory_list.end(), memory_regions);

	return memory_regions;
}
