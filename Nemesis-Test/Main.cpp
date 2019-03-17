#include <iostream>
#include <vector>
#include <Windows.h>
#include <winternl.h>

#pragma comment(lib,"ntdll.lib")

typedef struct _SYSTEM_PROCESS_INFO
{
	ULONG                   NextEntryOffset;
	ULONG                   NumberOfThreads;
	LARGE_INTEGER           Reserved[3];
	LARGE_INTEGER           CreateTime;
	LARGE_INTEGER           UserTime;
	LARGE_INTEGER           KernelTime;
	UNICODE_STRING          ImageName;
	ULONG                   BasePriority;
	HANDLE                  ProcessId;
	HANDLE                  InheritedFromProcessId;
}SYSTEM_PROCESS_INFO, *PSYSTEM_PROCESS_INFO;

struct PROCESS {
	HANDLE					ProcessId;
	UNICODE_STRING			ImageName;
};
struct DRIVER {
	std::string DriverName;
};

typedef std::vector<PROCESS *> (*GetProcessList)();
typedef std::vector<DRIVER *> (*GetDriverList)();

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
	// Function: GetProcessList
	//
	GetProcessList fGetProcessList = (GetProcessList)GetProcAddress(hModule, "GetProcessList");
	std::vector<PROCESS *> ProcessList = fGetProcessList();

	std::cout << "[DEBUG] Function located at: 0x" << std::hex << fGetProcessList << std::endl;
	std::cout << "Size: " << ProcessList.size() << std::endl;

	for (auto process : ProcessList)
	{
		std::cout << "Element: " << std::endl;
		std::cout << process->ImageName.Buffer << std::endl;
		std::cout << std::dec << process->ProcessId << std::endl;
		std::cout << std::endl;
	}


	//
	// Function: GetDriverList
	//
	//GetDriverList fGetDriverList = (GetDriverList)GetProcAddress(hModule, "GetDriverList");
	//std::vector<DRIVER *> DriverList = fGetDriverList();

	//std::cout << "[DEBUG] Function located at: 0x" << std::hex << fGetDriverList << std::endl;
	//std::cout << "Size: " << DriverList.size() << std::endl;

	//for (auto driver : DriverList)
	//{
	//	std::cout << "Element: " << std::endl;
	//	std::cout << driver->DriverName.c_str() << std::endl;
	//	std::cout << std::endl;
	//}



	std::cin.get();

	return EXIT_SUCCESS;
}