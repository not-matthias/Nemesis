#include <iostream>
#include <Windows.h>

int main() 
{
	//
	// Module
	//
	HMODULE hModule = LoadLibrary("D:\\Nemesis\\Nemesis\\x64\\Debug\\Nemesis.dll");

	if (hModule == NULL)
	{
		std::cout << "[DEBUG] Failed to open dll. (" << GetLastError() << ")" << std::endl;
		std::cin.get();
		return EXIT_FAILURE;
	}

	std::cout << "[DEBUG] Module located at: 0x" << std::hex << hModule << std::endl;

	//
	// Function
	//
	FARPROC fGetDriverList = GetProcAddress(hModule, "GetProcessList");
	if (fGetDriverList == NULL)
	{
		std::cout << "[DEBUG] Failed to get function. (" << std::dec <<  GetLastError() << ")" << std::endl;
		std::cin.get();
		return EXIT_FAILURE;
	}

	std::cout << "[DEBUG] Function located at: 0x" << std::hex << fGetDriverList << std::endl;



	std::cin.get();

	return EXIT_SUCCESS;
}