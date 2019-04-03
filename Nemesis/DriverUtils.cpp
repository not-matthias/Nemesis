#include "DriverUtils.hpp"
#include "Logger.hpp"

std::vector<DRIVER*> GetDriverList()
{
	std::vector<DRIVER*> driver_list;
	NTSTATUS status;

	//
	// Allocate Memory for the Module list
	//
	auto module_info = static_cast<PRTL_PROCESS_MODULES>(VirtualAlloc(
		nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));
	if (!module_info)
	{
		logger::Log("Unable to allocate Memory for Module list (%d)\n", GetLastError());
		return driver_list;
	}


	//
	// Get the Module list (SystemModuleInformation)
	//
	if (!NT_SUCCESS(status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(11), module_info, 1024 * 1024, NULL)))
	{
		logger::Log("Unable to query Module list (%#x)\n", status);
		VirtualFree(module_info, 0, MEM_RELEASE);
		return driver_list;
	}


	//
	// Loop though the modules
	//
	for (ULONG i = 0; i < module_info->number_of_modules; i++)
	{
		auto * driver = new DRIVER;
		driver->driver_name = std::string(
			reinterpret_cast<char*>(module_info->modules[i].full_path_name + module_info->modules[i].offset_to_file_name));

		driver_list.push_back(driver);
	}

	VirtualFree(module_info, 0, MEM_RELEASE);

	return driver_list;
}
