#include "DriverExport.hpp"

#include "DriverUtils.hpp"

auto GetDriverListElementExport(const UINT index, Driver *driver) -> BOOL
{
	const auto driver_list = DriverUtils::GetDriverList();

	//
	// Check if in bounds
	//
	if (index < 0 || index >= driver_list.size())
	{
		return FALSE;
	}

	//
	// Check if driver is valid
	//
	if(driver == nullptr)
	{
		return FALSE;
	}

	*driver = driver_list.at(index);

	return TRUE;
}
