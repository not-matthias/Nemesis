#pragma once

#include "IMemorySource.hpp"

#include <string>
#include <iostream>
#include <Windows.h>

//
// IOCTLs
//
#define IOCTL_READ_REQUEST				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2222, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_BASE_ADDRESS_REQUEST		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2223, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

//
// Structures
//

// DWORD is not defined in kernel thus I'm going to use ULONG, cause they are the same:
// - typedef unsigned long DWORD;
// - typedef unsigned long ULONG;
typedef struct _READ_REQUEST
{
	//
	// In
	//
	ULONG Pid;
	DWORD_PTR TargetAddress;

	//
	// Both
	//
	SIZE_T BufferSize;

	// 
	// Out
	// 
	PVOID BufferAddress;
} READ_REQUEST, *PREAD_REQUEST;

typedef struct _BASE_ADDRESS_REQUEST
{
	//
	// In
	//
	ULONG Pid;

	// 
	// Out
	// 
	PVOID BaseAddress;
} BASE_ADDRESS_REQUEST, *PBASE_ADDRESS_REQUEST;


class KernelMemory : IMemorySource
{
private:
	LPCSTR RegistryPath = "\\\\.\\KernelMemory";
	HANDLE hDriver = NULL;

public:
	KernelMemory(DWORD Pid);
	~KernelMemory();

	PVOID ReadMemory(DWORD_PTR StartAddress, SIZE_T Size);
	DWORD_PTR GetBaseAddress();
};

