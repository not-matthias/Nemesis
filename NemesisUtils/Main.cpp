#include <iostream>
#include "ProcessUtils.hpp"
#include "DriverUtils.hpp"

int main()
{
	std::cout << "Started." << std::endl;

	const auto index = 64;

	//
	// Process List
	//
	const auto processes = ProcessUtils::GetProcessList();
	std::cout << processes[index].process_information.image_name << std::endl;
	std::cout << processes[index].process_information.unique_process_id << std::endl;

	//
	// Module List
	//
	auto module_list = ProcessUtils::GetModuleList(12224);

	std::cout << "Size: " << module_list.size() << std::endl;

	for (auto && module : module_list)
	{
		std::cout << module.base_address << std::endl;
	}

	//
	// Driver List
	//
	//const auto driver_list = DriverUtils::GetDriverList();
	//std::cout << driver_list->drivers[5].full_path_name << std::endl;


	std::cout << "Finished." << std::endl;
}
