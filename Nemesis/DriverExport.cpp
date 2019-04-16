#include "DriverExport.hpp"
#include "DriverUtils.hpp"
#include <iostream>

auto GetDriverListExport(OUT DriverList* driver_list) -> void
{
	auto driver_list_vector = DriverUtils::GetDriverList();

	//
	// Allocate memory for the driver list
	//
	driver_list->drivers = new Driver[driver_list_vector.size()];

	//
	// Set the drivers in the array
	//
	for (auto i = 0; i < driver_list_vector.size(); ++i)
	{
		driver_list->drivers[i] = driver_list_vector[i];
	}
}
