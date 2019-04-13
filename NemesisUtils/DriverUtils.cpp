#include "DriverUtils.hpp"

#include <ostream>
#include <vector>

auto DriverUtils::GetDriverList() -> DriverList*
{
	const auto driver_list = new DriverList;
	std::vector<Driver> drivers;

	//
	// Allocate memory for the module list
	//
	const auto buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	const auto module_info = static_cast<PRTL_PROCESS_MODULES>(buffer);

	//
	// Check if the buffer is valid
	//
	if (!module_info)
	{
		return nullptr;
	}

	//
	// Query the system information (aka drivers)
	//
	if (!NT_SUCCESS(NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(11), module_info, 1024 * 1024, NULL)))
	{
		VirtualFree(module_info, 0, MEM_RELEASE);
		return nullptr;
	}

	//
	// Loop through the drivers
	//
	for (ULONG i = 0; i < module_info->number_of_modules; i++)
	{
		//
		// Create a new driver
		//
		Driver driver{};
		driver.image_base = module_info->Modules[i].image_base;
		driver.image_size = module_info->Modules[i].image_size;
		driver.offset_to_file_name = module_info->Modules[i].offset_to_file_name;

		const auto full_path_name = module_info->Modules[i].full_path_name;
		std::string path_name(full_path_name, full_path_name + strlen(reinterpret_cast<const char*>(full_path_name)));
		std::copy(path_name.begin(), path_name.end(), driver.full_path_name);

		//
		// Add the driver to the list
		//
		drivers.push_back(driver);
	}

	//
	// Add the drivers to the actual list
	//
	driver_list->drivers = new Driver[drivers.size()];
	std::copy(drivers.begin(), drivers.end(), driver_list->drivers);

	//
	// Free the buffer
	//
	VirtualFree(module_info, 0, MEM_RELEASE);

	return driver_list;
}
