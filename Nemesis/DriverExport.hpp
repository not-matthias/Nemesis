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
 * \brief Creates a new driver_list list.
 * \param driver_list the output buffer.
 */
auto GetDriverListExport(OUT DriverList * driver_list) -> VOID;
