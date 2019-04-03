#pragma once

#include <Windows.h>

class IMemorySource
{
protected:
	DWORD process_id;

public:
	virtual ~IMemorySource() = default;
	explicit IMemorySource(DWORD process_id);

	virtual PVOID ReadMemory(DWORD_PTR start_address, SIZE_T size) = 0;

	virtual DWORD_PTR GetBaseAddress() = 0;
};