#include "stdafx.h"

#include "DriverUtils.hpp"

auto DriverUtils::GetDriverList() -> std::vector<Driver>
{
	//
	// Allocate memory for the module list
	//
	const auto buffer = VirtualAlloc(nullptr, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	std::unique_ptr<RTL_PROCESS_MODULES, MemoryDisposer> module_info(reinterpret_cast<PRTL_PROCESS_MODULES>(buffer), MemoryDisposer{});

	//
	// Check if the buffer is valid
	//
	if (!module_info)
	{
		return {};
	}

	//
	// Query the system information (aka drivers)
	//
	if (!NT_SUCCESS(NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(11), module_info.get(), 1024 * 1024, NULL)))
	{
		return {};
	}

	//
	// Create driver list
	//
	std::vector<Driver> drivers;
	drivers.reserve(module_info->number_of_modules);

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
		const auto string_size = std::strlen(reinterpret_cast<char const *>(full_path_name));
		//std::copy(full_path_name[0], full_path_name[string_size], driver.full_path_name);
		// TODO: Find proper way to do this.

		//
		// Add the driver to the list
		//
		drivers.push_back(driver);
	}

	return drivers;
}
