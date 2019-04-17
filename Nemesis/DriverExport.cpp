#include "DriverExport.hpp"

#include "DriverUtils.hpp"

auto GetDriverListElementExport(const UINT index, Driver driver) -> BOOL
{
	const auto driver_list = DriverUtils::GetDriverList();

	//
	// Check if in bounds
	//
	if (index < 0 || index >= driver_list.size())
	{
		return FALSE;
	}

	driver = driver_list[index];

	return TRUE;
}
