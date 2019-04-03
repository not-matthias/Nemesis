#pragma once

#include "IMemorySource.hpp"
#include <Windows.h>

class UsermodeMemory final : public IMemorySource
{
	HANDLE process_handle = nullptr;

public:
	explicit UsermodeMemory(DWORD process_id);
	virtual ~UsermodeMemory();

	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) -> PVOID override;
	auto GetBaseAddress() -> DWORD_PTR override;
};
