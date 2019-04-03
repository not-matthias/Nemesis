#include "ProcessMemory.hpp"
#include "UsermodeMemory.hpp"

ProcessMemory::ProcessMemory(const DWORD process_id)
{
	this->process_id = process_id;
	this->memory_source = new UsermodeMemory(process_id);
}

ProcessMemory::~ProcessMemory()
{
	delete memory_source;
}

template <typename T>
auto ProcessMemory::ReadMemory(const DWORD_PTR start_address) -> T
{
	return reinterpret_cast<T>(this->memory_source->ReadMemory(start_address, sizeof(T)));
}

template <typename T>
auto ProcessMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) -> T
{
	return reinterpret_cast<T>(this->memory_source->ReadMemory(start_address, size));
}

auto ProcessMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) const -> PVOID
{
	return this->memory_source->ReadMemory(start_address, size);
}

auto ProcessMemory::IsValid() const -> BOOL
{
	return memory_source != nullptr;
}

auto ProcessMemory::GetBaseAddress() const -> DWORD_PTR
{
	return memory_source->GetBaseAddress();
}
