#include "ProcessUtils.hpp"
#include "Logger.hpp"

auto GetProcessList() -> std::vector<PROCESS*>
{
	std::vector<PROCESS*> process_list;
	NTSTATUS status;

	//
	// Allocate Memory for the list
	//
	auto const buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!buffer)
	{
		logger::Log("Failed to allocate memory_buffer.\n");

		// Free the memory_buffer
		VirtualFree(buffer, 0, MEM_RELEASE);

		return process_list;
	}

	auto system_process_info = static_cast<PSYSTEM_PROCESS_INFO>(buffer);

	//
	// Get the process list
	//
	if (!NT_SUCCESS(status = NtQuerySystemInformation(SystemProcessInformation, system_process_info, 1024 * 1024, NULL)))
	{
		logger::Log("Unable to query process list (%#x)\n", status);

		// Free the memory_buffer
		VirtualFree(buffer, 0, MEM_RELEASE);

		return process_list;
	}

	//
	// Loop over the processes
	//
	while (system_process_info->next_entry_offset)
	{
		auto process = new PROCESS;
		process->image_name = system_process_info->image_name;
		process->process_id = system_process_info->process_id;

		// Add the process to the list
		process_list.push_back(process);

		// Calculate the address of the next entry
		system_process_info = reinterpret_cast<PSYSTEM_PROCESS_INFO>(reinterpret_cast<LPBYTE>(system_process_info) + system_process_info->
			next_entry_offset);
	}

	// Free the memory_buffer
	VirtualFree(buffer, 0, MEM_RELEASE);

	return process_list;
}
