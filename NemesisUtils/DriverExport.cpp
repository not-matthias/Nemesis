#include "DriverExport.hpp"
#include "DriverUtils.hpp"

auto GetDriverList(DriverList * driver_list) -> void
{
	driver_list = DriverUtils::GetDriverList();
}
