#include "ProcessExport.hpp"

#include "ProcessUtils.hpp"

auto GetProcessListElementExport(const UINT index, Process *process) -> BOOL
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
