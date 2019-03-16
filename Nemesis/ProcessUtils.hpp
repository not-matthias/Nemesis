#pragma once

#include "Logger.hpp"

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

//typedef struct _SYSTEM_PROCESS_INFORMATION {
//	ULONG NextEntryOffset;
//	ULONG NumberOfThreads;
//	BYTE Reserved1[48];
//	UNICODE_STRING ImageName;
//	KPRIORITY BasePriority;
//	HANDLE UniqueProcessId;
//	PVOID Reserved2;
//	ULONG HandleCount;
//	ULONG SessionId;
//	PVOID Reserved3;
//	SIZE_T PeakVirtualSize;
//	SIZE_T VirtualSize;
//	ULONG Reserved4;
//	SIZE_T PeakWorkingSetSize;
//	SIZE_T WorkingSetSize;
//	PVOID Reserved5;
//	SIZE_T QuotaPagedPoolUsage;
//	PVOID Reserved6;
//	SIZE_T QuotaNonPagedPoolUsage;
//	SIZE_T PagefileUsage;
//	SIZE_T PeakPagefileUsage;
//	SIZE_T PrivatePageCount;
//	LARGE_INTEGER Reserved7[6];
//} SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFO;



struct PROCESS
{
	HANDLE					ProcessId;
	UNICODE_STRING			ImageName;
};

namespace ProcessHelper
{
	std::vector<PROCESS *> &GetProcessList();
};

