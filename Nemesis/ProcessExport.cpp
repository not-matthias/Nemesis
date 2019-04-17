#include "ProcessExport.hpp"

#include "ProcessUtils.hpp"

auto GetProcessListElementExport(const UINT index, Process process) -> BOOL
{
	const auto process_list = ProcessUtils::GetProcessList();

	//
	// Check if in bounds
	//
	if (index < 0 || index >= process_list.size())
	{
		return FALSE;
	}

	process = process_list[index];

	return TRUE;
}
