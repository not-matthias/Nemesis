#pragma once

#include <vector>
#include <Windows.h>
#include <winternl.h>

#include "DriverExport.hpp"

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

typedef struct _RTL_PROCESS_MODULES
{
	ULONG number_of_modules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;


class DriverUtils
{
public:
	/**
	 * \brief Creates the driver list.
	 * \return the driver list
	 */
	static auto GetDriverList() -> std::vector<Driver>;
};
