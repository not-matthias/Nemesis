#include <iostream>
#include "ProcessUtils.hpp"

int main()
{
	std::cout << "Started." << std::endl;

	//auto module_list = ProcessUtils::GetModuleList(23024);

	//auto process_list = ProcessUtils::GetProcessList();
	//std::cout << process_list->processes[10].process_information.image_name << std::endl;

	ProcessUtils::GetMemoryRegions(3136);

	std::cout << "Finished." << std::endl;
	std::cin.get();
}
