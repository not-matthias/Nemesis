#pragma once

#include "IMemorySource.hpp"
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
	ULONG process_id;
	DWORD_PTR target_address;

	//
	// Both
	//
	SIZE_T buffer_size;

	// 
	// Out
	// 
	PVOID buffer_address;
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


class KernelMemory final : IMemorySource
{
	LPCWSTR registry_path = L"\\\\.\\KernelMemory";
	HANDLE driver_handle = nullptr;

public:
	explicit KernelMemory(DWORD process_id);
	~KernelMemory();

	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> PVOID override;
	auto GetBaseAddress() -> DWORD_PTR override;
};