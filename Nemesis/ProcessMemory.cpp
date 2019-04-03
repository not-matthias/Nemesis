#include "ProcessMemory.hpp"
#include "UsermodeMemory.hpp"

ProcessMemory::ProcessMemory(const DWORD process_id)
{
	this->process_id = process_id;
	this->memory_source = new UsermodeMemory(process_id);
}

ProcessMemory::~ProcessMemory() = default;

//
// Functions
//
template<typename T>
T ProcessMemory::ReadMemory(DWORD_PTR start_address)
{
	return reinterpret_cast<T>(this->memory_source->ReadMemory(start_address, sizeof(T)));
}

PVOID ProcessMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) const
{
	return this->memory_source->ReadMemory(start_address, size);
}

//
// Getters
//
DWORD_PTR ProcessMemory::GetBaseAddress() const
{
	return memory_source->GetBaseAddress();
}

//
// Checks
//
BOOL ProcessMemory::IsValid() const
{
	return memory_source != nullptr;
}
