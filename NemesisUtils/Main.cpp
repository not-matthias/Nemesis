#include <iostream>
#include "ProcessUtils.hpp"
#include "DriverUtils.hpp"

int main()
{
	std::cout << "Started." << std::endl;

	
	//
	// Process List
	//
	const auto process_list = ProcessUtils::GetProcessList();
	//std::cout << process_list->processes[5].process_information.image_name << std::endl;
	//std::cout << process_list->processes[5].modules[8].module_name<< std::endl;
	//std::cout << process_list->processes[5].memory_regions[5].base_address<< std::endl;

	const auto module_list = ProcessUtils::GetModuleList(6196);


	//
	// Driver List
	//
	//const auto driver_list = DriverUtils::GetDriverList();
	//std::cout << driver_list->drivers[5].full_path_name << std::endl;


	std::cout << "Finished." << std::endl;
}
