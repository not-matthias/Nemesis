#include <iostream>
#include "ProcessUtils.hpp"
#include "DriverUtils.hpp"

int main()
{
	std::cout << "Started." << std::endl;

	
	//
	// Process List
	//
	//const auto process_list = ProcessUtils::GetProcessList();
	//std::cout << process_list->processes[5].process_information.image_name << std::endl;

	//
	// Driver List
	//
	const auto driver_list = DriverUtils::GetDriverList();
	std::cout << driver_list->drivers[5].full_path_name << std::endl;



	std::cout << "Finished." << std::endl;
}
