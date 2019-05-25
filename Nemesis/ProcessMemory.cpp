#include "stdafx.h"

#include "MemorySource.h"
#include "ProcessMemory.hpp"
#include "UsermodeMemory.hpp"

ProcessMemory::ProcessMemory(const DWORD process_id)
{
	this->process_id = process_id;
}

ProcessMemory::~ProcessMemory() = default;

auto ProcessMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) const -> PVOID
{
	return MemorySource::GetMemorySource(process_id)->ReadMemory(start_address, size);
}

auto ProcessMemory::IsValid() const -> BOOL
{
	return MemorySource::GetMemorySource(process_id)->IsValid();
}

auto ProcessMemory::GetBaseAddress() const -> DWORD_PTR
{
	return MemorySource::GetMemorySource(process_id)->GetBaseAddress();
}

auto ProcessMemory::GetProcessId() const -> DWORD
{
	return process_id;
}
