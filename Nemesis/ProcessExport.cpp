#include "stdafx.h"

#include "ProcessExport.hpp"
#include "ProcessUtils.hpp"

std::vector<ProcessElement> process_list;
std::vector<ModuleElement> module_list;
std::vector<MemoryElement> memory_list;

auto GetProcessListElementExport(const UINT index, ProcessElement * process) -> BOOL
{
	//
	// Check if in bounds
	//
	if (index < 0 || index >= process_list.size())
	{
		return FALSE;
	}

	//
	// Check if first request (load process list)
	//
	if(index == 0)
	{
		process_list = ProcessUtils::GetProcessList();
	}

	//
	// Check if process is valid
	//
	if (process == nullptr)
	{
		return FALSE;
	}

	*process = process_list.at(index);

	return TRUE;
}

auto GetModuleListElementExport(const UINT index, const DWORD process_id, ModuleElement * module) -> BOOL
{
	//
	// Check if in bounds
	//
	if (index < 0 || index >= module_list.size())
	{
		return FALSE;
	}

	//
	// Check if first request (load module list)
	//
	if (index == 0)
	{
		module_list = ProcessUtils::GetModuleList(process_id);
	}

	//
	// Check if module is valid
	//
	if (module == nullptr)
	{
		return FALSE;
	}

	*module = module_list.at(index);

	return TRUE;
}

auto GetModuleListManualElementExport(const UINT index, const DWORD process_id, ModuleElement * module) -> BOOL
{
	//
	// Check if in bounds
	//
	if (index < 0 || index >= module_list.size())
	{
		return FALSE;
	}

	//
	// Check if first request (load module list)
	//
	if (index == 0)
	{
		module_list = ProcessUtils::GetModuleListManually(process_id);
	}

	//
	// Check if module is valid
	//
	if (module == nullptr)
	{
		return FALSE;
	}

	*module = module_list.at(index);

	return TRUE;
}

auto GetMemoryListElementExport(const UINT index, const DWORD process_id, MemoryElement * memory) -> BOOL
{
	//
	// Check if in bounds
	//
	if (index < 0 || index >= memory_list.size())
	{
		return FALSE;
	}

	//
	// Check if first request (load memory list)
	//
	if (index == 0)
	{
		memory_list = ProcessUtils::GetMemoryList(process_id);
	}

	//
	// Check if memory is valid
	//
	if (memory == nullptr)
	{
		return FALSE;
	}

	*memory = memory_list.at(index);

	return TRUE;
}
