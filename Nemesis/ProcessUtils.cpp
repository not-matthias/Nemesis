#include "ProcessUtils.hpp"

std::vector<PROCESS *> ProcessHelper::GetProcessList()
{
	std::vector<PROCESS *> List;
	PVOID pBuffer;
	NTSTATUS Status;
	PSYSTEM_PROCESS_INFO pSystemProcessInfo = { 0 };

	//
	// Allocate memory for the list
	//
	pBuffer = VirtualAlloc(NULL, 1024 * 1024, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!pBuffer)
	{
		Logger::Log("Failed to allocate buffer.\n");
		goto EXIT;
	}

	pSystemProcessInfo = (PSYSTEM_PROCESS_INFO)pBuffer;

	//
	// Get the process list
	//
	if (!NT_SUCCESS(Status = NtQuerySystemInformation(SystemProcessInformation, pSystemProcessInfo, 1024 * 1024, NULL)))
	{
		Logger::Log("Unable to query process list (%#x)\n", Status);
		goto EXIT;
	}

	//
	// Loop over the processes
	//
	while (pSystemProcessInfo->NextEntryOffset)
	{
		PROCESS *pProcess = new PROCESS;
		pProcess->ImageName = pSystemProcessInfo->ImageName;
		pProcess->ProcessId = pSystemProcessInfo->ProcessId;

		// Add the process to the list
		List.push_back(pProcess);

		// Calculate the address of the next entry
		pSystemProcessInfo = (PSYSTEM_PROCESS_INFO)((LPBYTE)pSystemProcessInfo + pSystemProcessInfo->NextEntryOffset);
	}

EXIT:
	// Free the buffer
	VirtualFree(pBuffer, 0, MEM_RELEASE);

	return List;
}