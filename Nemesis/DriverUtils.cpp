#include "DriverUtils.hpp"

std::vector<DRIVER *> DriverHelper::GetDriverList()
{
	std::vector<DRIVER *> List;
	NTSTATUS Status;
	ULONG i;

	PRTL_PROCESS_MODULES ModuleInfo;

	//
	// Allocate memory for the module list
	//
	ModuleInfo = (PRTL_PROCESS_MODULES)VirtualAlloc(NULL, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!ModuleInfo)
	{
		Logger::Log("Unable to allocate memory for module list (%d)\n", GetLastError());
		return List;
	}


	//
	// Get the module list (SystemModuleInformation)
	//
	if (!NT_SUCCESS(Status = NtQuerySystemInformation((SYSTEM_INFORMATION_CLASS)11, ModuleInfo, 1024 * 1024, NULL)))
	{
		Logger::Log("Unable to query module list (%#x)\n", Status);
		VirtualFree(ModuleInfo, 0, MEM_RELEASE);
		return List;
	}


	//
	// Loop though the modules
	//
	for (i = 0; i < ModuleInfo->NumberOfModules; i++)
	{
		DRIVER *pDriver = new DRIVER;
		pDriver->DriverName = std::string(reinterpret_cast<char *>(ModuleInfo->Modules[i].FullPathName + ModuleInfo->Modules[i].OffsetToFileName));

		List.push_back(pDriver);
	}

	VirtualFree(ModuleInfo, 0, MEM_RELEASE);

	return List;
}