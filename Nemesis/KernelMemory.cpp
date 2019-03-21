#include "KernelMemory.hpp"

KernelMemory::KernelMemory(DWORD Pid) : IMemorySource(Pid)
{
	//
	// Create connection to the driver
	//
	hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
}

KernelMemory::~KernelMemory()
{
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDriver);
	}
}

PVOID KernelMemory::ReadMemory(DWORD_PTR StartAddress, SIZE_T Size)
{
	//
	// Checks
	//
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	//
	// Create the struct
	//
	READ_REQUEST ReadRequest;
	ReadRequest.Pid = Pid;
	ReadRequest.TargetAddress = StartAddress;
	ReadRequest.BufferSize = Size;

	//
	// Send the struct
	//
	if (DeviceIoControl(hDriver, IOCTL_READ_REQUEST, &ReadRequest, sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0))
	{
		return ReadRequest.BufferAddress;
	}
	else
	{
		return NULL;
	}
}

DWORD_PTR KernelMemory::GetBaseAddress()
{
	//
	// Checks
	//
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	//
	// Create the struct
	//
	BASE_ADDRESS_REQUEST BaseAddressRequest;
	BaseAddressRequest.Pid = Pid;

	//
	// Send the struct
	//
	if (DeviceIoControl(hDriver, IOCTL_BASE_ADDRESS_REQUEST, &BaseAddressRequest, sizeof(BaseAddressRequest), &BaseAddressRequest, sizeof(BaseAddressRequest), 0, 0))
	{
		return BaseAddressRequest.BaseAddress;
	}
	else
	{
		return NULL;
	}
}
