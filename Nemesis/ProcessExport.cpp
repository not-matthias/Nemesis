#include "ProcessExport.hpp"

#include "ProcessUtils.hpp"

auto GetProcessListElementExport(const UINT index, ProcessElement * process) -> BOOL
{
	const auto process_list = ProcessUtils::GetProcessList();

	//
	// Check if in bounds
	//
	if (index < 0 || index >= process_list.size())
	{
		return FALSE;
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
	const auto module_list = ProcessUtils::GetModuleList(process_id);

	//
	// Check if in bounds
	//
	if (index < 0 || index >= module_list.size())
	{
		return FALSE;
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
	const auto memory_list = ProcessUtils::GetMemoryList(process_id);

	//
	// Check if in bounds
	//
	if (index < 0 || index >= memory_list.size())
	{
		return FALSE;
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
