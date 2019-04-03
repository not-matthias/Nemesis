#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>
#include <winternl.h>

/**
 * \brief The structure for the module information.
 */
typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE section;
	PVOID mapped_base;
	PVOID image_base;
	ULONG image_size;
	ULONG flags;
	USHORT load_order_index;
	USHORT init_order_index;
	USHORT load_count;
	USHORT offset_to_file_name;
	UCHAR full_path_name[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;


/**
 * \brief The structure for the driver enumeration.
 */
typedef struct _RTL_PROCESS_MODULES
{
	ULONG number_of_modules;
	RTL_PROCESS_MODULE_INFORMATION modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;


/**
 * \brief The structure for the driver list.
 */
struct DRIVER {
	std::string driver_name;
};


/**
 * \brief Returns a list of drivers.
 * \return the driver list
 */
auto GetDriverList() -> std::vector<DRIVER *>;
