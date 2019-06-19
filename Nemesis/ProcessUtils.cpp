#include "stdafx.h"

#include "DriverUtils.hpp"
#include "Logger.hpp"
#include "ProcessUtils.hpp"
#include "MemorySource.h"
#include "SmartHandle.hpp"

auto ProcessUtils::GetProcessList() -> std::vector<ProcessElement>
{
	std::vector<ProcessElement> processes;

	//
	// Allocate memory for the buffer
	//
	const auto unsafe_buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	std::unique_ptr<BYTE, MemoryDisposer> buffer(static_cast<BYTE*>(unsafe_buffer), MemoryDisposer{});
	if (!buffer)
	{
		return {};
	}

	//
	// Create the process info buffer
	//

	//
	// Get the process list
	//
	if (!NT_SUCCESS(NtQuerySystemInformation(SystemProcessInformation, buffer.get(), 1024 * 1024, NULL)))
	{
		return {};
	}

	//
	// Create the process list
	//
	auto system_process_info = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(buffer.get())	;
	while (system_process_info->NextEntryOffset)
	{
		//
		// Create the process struct
		//
		std::wstring image_name(system_process_info->ImageName.Buffer, static_cast<UINT64>(system_process_info->ImageName.Length / 2));
		std::string string(image_name.begin(), image_name.end());
		ProcessElement process{};

		std::copy(string.begin(), string.end(), reinterpret_cast<char*>(process.image_name));
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
		//process_list->processes[index++] = process;
		processes.push_back(process);

		//
		// Calculate the next offset
		//
		system_process_info = reinterpret_cast<PSYSTEM_PROCESS_INFORMATION>(reinterpret_cast<LPBYTE>(system_process_info) + system_process_info->NextEntryOffset
		);
	}

	return processes;
}

auto ProcessUtils::GetModuleList(const DWORD process_id) -> std::vector<ModuleElement>
{
	//
	// Open the process
	//
	const auto process_handle = SmartHandle(OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id));
	if (!process_handle.IsValid())
	{
		Logger::Log("Failed to get process handle.");
		return {};
	}

	//
	// Loop through the modules
	//
	std::vector<ModuleElement> modules;
	HMODULE module_handles[1024];
	DWORD cb_needed;
	if (EnumProcessModules(process_handle.Get(), module_handles, sizeof(module_handles), &cb_needed))
	{
		modules.reserve(cb_needed / sizeof(HMODULE));

		for (unsigned long i = 0; i < cb_needed / sizeof(HMODULE); i++)
		{
			WCHAR file_path[MAX_PATH];

			//
			// Get the full path
			//
			if (!GetModuleFileNameEx(process_handle.Get(), module_handles[i], file_path, sizeof(file_path) / sizeof(CHAR)))
			{
				Logger::Log("Failed to get file path.");
				continue;
			}

			//
			// Get module information
			//
			MODULEINFO module_info = {0};
			if (!GetModuleInformation(process_handle.Get(), module_handles[i], &module_info, sizeof(module_info)))
			{
				Logger::Log("Failed to get module information.");
				continue;
			}

			//
			// Create a new module
			//
			ModuleElement module{};

			module.base_address = module_info.lpBaseOfDll;
			module.module_size = module_info.SizeOfImage;

			std::wstring module_file_path(file_path);
			std::copy(module_file_path.begin(), module_file_path.end(), reinterpret_cast<char*>(module.module_path));

			const auto module_file_name = module_file_path.substr(module_file_path.find_last_of(L"/\\") + 1);
			std::copy(module_file_name.begin(), module_file_name.end(), reinterpret_cast<char*>(module.module_name));

			//
			// Add it to the list
			//
			modules.push_back(module);
		}
	}

	return modules;
}

auto ProcessUtils::GetModuleListManually(const DWORD process_id) -> std::vector<ModuleElement>
{
	const auto memory_source = MemorySource::GetMemorySource(process_id);

	Logger::Log("Creating module list manually.");

	//
	// Get process handle
	//
	const auto process_handle = SmartHandle(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id));
	if (!process_handle.IsValid())
	{
		Logger::Log("Failed to get process handle.");
		return {};
	}

	//
	// PROCESS_BASIC_INFORMATION
	//
	structs::PROCESS_BASIC_INFORMATION pbi = {0};
	if (!NT_SUCCESS(NtQueryInformationProcess(process_handle.Get(), ProcessBasicInformation, &pbi, sizeof(pbi), nullptr)))
	{
		Logger::Log("Could not get process information.");
		return {};
	}

	//
	// PEB
	//
	const auto peb_memory = memory_source->ReadMemory(reinterpret_cast<DWORD_PTR>(pbi.PebBaseAddress), sizeof(structs::PEB));
	const auto peb = std::reinterpret_pointer_cast<structs::PEB>(peb_memory);

	if (peb_memory == nullptr || peb == nullptr)
	{
		Logger::Log("Failed to read PEB from process.");
		return {};
	}

	//
	// PEB_LDR_DATA
	//
	const auto peb_ldr_data_memory = memory_source->ReadMemory(reinterpret_cast<DWORD_PTR>(peb->Ldr), sizeof(structs::PEB_LDR_DATA));
	const auto peb_ldr_data = std::reinterpret_pointer_cast<structs::PEB_LDR_DATA>(peb_ldr_data_memory);

	if (peb_ldr_data_memory == nullptr || peb_ldr_data == nullptr)
	{
		Logger::Log("Failed to read module list from process.");
		return {};
	}

	//
	// LIST_ENTRY
	//
	const auto ldr_list_head = static_cast<LIST_ENTRY *>(peb_ldr_data->InLoadOrderModuleList.Flink);
	auto ldr_current_node = peb_ldr_data->InLoadOrderModuleList.Flink;

	// 
	// Loop through the modules
	// 
	std::vector<ModuleElement> modules;
	do
	{
		//
		// LDR_DATA_TABLE_ENTRY
		//
		const auto list_entry_memory = memory_source->ReadMemory(reinterpret_cast<DWORD_PTR>(ldr_current_node), sizeof(structs::LDR_DATA_TABLE_ENTRY));
		const auto list_entry = std::reinterpret_pointer_cast<structs::LDR_DATA_TABLE_ENTRY>(list_entry_memory);

		if (list_entry_memory == nullptr || list_entry == nullptr)
		{
			Logger::Log("Could not read list entry from LDR list.");
			return {};
		}

		//
		// Add the module to the list
		//
		if (list_entry->DllBase != nullptr && list_entry->SizeOfImage != 0)
		{
			ModuleElement module{};
			module.base_address = list_entry->DllBase;
			module.module_size = list_entry->SizeOfImage;

			if (list_entry->BaseDllName.Length > 0)
			{
				const auto buffer = memory_source->ReadMemory(reinterpret_cast<DWORD_PTR>(list_entry->BaseDllName.Buffer), list_entry->BaseDllName.Length);
				if (buffer != nullptr)
				{
					std::wstring base_dll_name(reinterpret_cast<PWCHAR>(buffer.get()), list_entry->BaseDllName.Length / 2);
					std::copy(base_dll_name.begin(), base_dll_name.end(), reinterpret_cast<char*>(module.module_name));
				}
			}

			if (list_entry->FullDllName.Length > 0)
			{
				const auto buffer = memory_source->ReadMemory(reinterpret_cast<DWORD_PTR>(list_entry->FullDllName.Buffer), list_entry->FullDllName.Length);
				if (buffer != nullptr)
				{
					std::wstring full_dll_name(reinterpret_cast<PWCHAR>(buffer.get()), list_entry->FullDllName.Length / 2);
					std::copy(full_dll_name.begin(), full_dll_name.end(), reinterpret_cast<char*>(module.module_path));
				}
			}

			modules.push_back(module);
		}

		ldr_current_node = list_entry->InLoadOrderLinks.Flink;
	}
	while (ldr_list_head != ldr_current_node);

	return modules;
}

auto ProcessUtils::GetMemoryList(const DWORD process_id) -> std::vector<MemoryElement>
{
	//
	// Open the process
	//
	const auto process_handle = SmartHandle(OpenProcess(PROCESS_ALL_ACCESS, false, process_id));
	if (!process_handle.IsValid())
	{
		return {};
	}

	MEMORY_BASIC_INFORMATION memory_basic_information;

	// 
	// Loop through the memory regions
	// 
	std::vector<MemoryElement> memory_list;
	for (BYTE * memory_region_start = nullptr;
	     VirtualQueryEx(process_handle.Get(), memory_region_start, &memory_basic_information, sizeof(MEMORY_BASIC_INFORMATION64));
	     memory_region_start += memory_basic_information.RegionSize)
	{
		//
		// Creates a new memory source
		//
		MemoryElement memory{};
		memory.base_address = memory_basic_information.BaseAddress;
		memory.region_size = memory_basic_information.RegionSize;
		memory.state = memory_basic_information.State; // (MEM_COMMIT | MEM_FREE | MEM_RESERVE)
		memory.type = memory_basic_information.Type; // (MEM_IMAGE | MEM_MAPPED | MEM_PRIVATE)

		//
		// Add it to the list
		//
		memory_list.push_back(memory);
	}

	return memory_list;
}

auto ProcessUtils::GetFilePath(const DWORD process_id) -> std::wstring
{
	std::wstring path(MAX_PATH, '\0');
	DWORD length = 0;

	//
	// Get the path
	//
	const auto process_handle = SmartHandle(OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id));
	if (process_handle.IsValid())
	{
		if (!(length = GetModuleFileNameEx(process_handle.Get(), nullptr, const_cast<LPWSTR>(path.data()), path.size())))
		{
			Logger::Log("Failed to get module file name.");
		}
	}
	else
	{
		Logger::Log("Failed to open file.");
	}

	//
	// Adjust size
	//
	path.resize(length);

	return path;
}
