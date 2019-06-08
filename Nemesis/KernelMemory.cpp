#include "stdafx.h"

#include "KernelMemory.hpp"

KernelMemory::KernelMemory(const DWORD process_id) : IMemorySource(process_id)
{
	//
	// Create connection to the driver
	//
	driver_handle = CreateFileW(registry_path, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
	                            NULL, nullptr);
}

KernelMemory::~KernelMemory()
{
	if (driver_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(driver_handle);
	}
}

auto KernelMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) -> std::shared_ptr<BYTE>
{
	//
	// Checks
	//
	if (driver_handle == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	//
	// Create the struct
	//
	READ_REQUEST read_request;
	read_request.process_id = process_id;
	read_request.target_address = start_address;
	read_request.buffer_address = new BYTE[size];
	read_request.buffer_size = size;

	//
	// Send the struct
	//
	if (DeviceIoControl(driver_handle, IOCTL_READ_REQUEST, &read_request, sizeof(read_request), &read_request, sizeof(read_request), nullptr, nullptr))
	{
		const auto buffer = std::shared_ptr<BYTE>(read_request.buffer_address, [](BYTE* p) {delete[] p; });
		return buffer;
	}
	else
	{
		return nullptr;
	}
}

auto KernelMemory::IsValid() -> BOOL
{
	//
	// Check if handle is valid
	//
	if (driver_handle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	return TRUE;
}

auto KernelMemory::GetBaseAddress() -> DWORD_PTR
{
	//
	// Checks
	//
	if (driver_handle == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	//
	// Create the struct
	//
	BASE_ADDRESS_REQUEST base_address_request;
	base_address_request.process_id = process_id;

	//
	// Send the struct
	//
	if (DeviceIoControl(driver_handle, IOCTL_BASE_ADDRESS_REQUEST, &base_address_request, sizeof(base_address_request), &base_address_request,
	                    sizeof(base_address_request), nullptr, nullptr))
	{
		return reinterpret_cast<DWORD_PTR>(base_address_request.base_address);
	}
	else
	{
		return NULL;
	}
}
