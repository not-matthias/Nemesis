#include "DriverExport.hpp"

#include <fstream>

#include "DriverUtils.hpp"
#include "Logger.hpp"

auto GetDriverListElementExport(const UINT index, Driver * driver) -> BOOL
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
	if (driver == nullptr)
	{
		return FALSE;
	}

	*driver = driver_list.at(index);

	return TRUE;
}

auto SaveDriverInformationExport(const LPCSTR file_name) -> BOOL
{
	const auto driver_list = DriverUtils::GetDriverList();

	std::ofstream output_file;

	//
	// Open file
	//
	try
	{
		output_file.open(file_name, std::ios::app);
	}
	catch (std::exception & e)
	{
		Logger::Log(e.what());
		return FALSE;
	}

	//
	// Write to file
	//
	for (auto && driver : driver_list)
	{
		output_file << driver.full_path_name + driver.offset_to_file_name;
		output_file << " -> 0x" << driver.image_base;
		output_file << " (" << std::hex << driver.image_size << ")" << std::endl;
	}

	//
	// Close file
	//
	output_file.close();

	return TRUE;
}
