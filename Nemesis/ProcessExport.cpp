#include "ProcessExport.hpp"
#include "ProcessUtils.hpp"

auto GetProcessListExport(OUT ProcessList * process_list) -> VOID
{
	auto process_list_vector = ProcessUtils::GetProcessList();

	//
	// Allocate memory for the process list
	//
	process_list->processes = new Process[process_list_vector.size()];

	//
	// Set the processes in the array
	//
	for (auto i = 0; i < process_list_vector.size(); ++i)
	{
		process_list->processes[i] = process_list_vector[i];
	}
}
