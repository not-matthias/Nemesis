#pragma once

#include <Windows.h>

/**
 * \brief Contains the driver data.
 */
struct Driver
{
	PVOID image_base;
	ULONG image_size;
	USHORT offset_to_file_name;
	UCHAR full_path_name[256];
};

/**
 * \brief Contains the list of drivers.
 */
struct DriverList
{
	Driver * drivers;
};


/**
 * \brief Returns the driver at the specified index. (C# has maximal struct size)
 * \param index the index in the list
 * \param driver the driver at the index
 * \return true if successful
 */
auto GetDriverListElementExport(IN UINT index, OUT Driver *driver) -> BOOL;