#include "stdafx.h"

#include "DriverUtils.hpp"

auto DriverUtils::GetDriverList() -> std::vector<Driver>
{
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
		return std::vector<Driver>();
	}

	//
	// Query the system information (aka drivers)
	//
	if (!NT_SUCCESS(NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(11), module_info, 1024 * 1024, NULL))
	)
	{
		VirtualFree(module_info, 0, MEM_RELEASE);
		return std::vector<Driver>();
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
	// Free the buffer
	//
	VirtualFree(module_info, 0, MEM_RELEASE);

	return drivers;
}
