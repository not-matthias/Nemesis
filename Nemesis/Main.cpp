#include <Windows.h>

#include "Dump.hpp"
#include "KernelMemory.hpp"

int main()
{
	//
	// Get the pid
	//
	DWORD Pid;
	std::cout << "Enter Pid: ";
	std::cin >> Pid;

	//
	// Create the classes
	//



	//Dump ProcessDump(24540);
	try
	{
		//
		// Create the classes
		//
		KernelMemory Memory(Pid);

		//
		// Print the base address
		//
		DWORD_PTR BaseAddress = Memory.GetBaseAddress();
		std::cout << "BaseAddress: 0x" << std::hex << BaseAddress << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Failed: " << e.what() << std::endl;
	}



	std::cin.get();
	return EXIT_SUCCESS;
}