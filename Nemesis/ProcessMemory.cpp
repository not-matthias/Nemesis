#include "ProcessMemory.hpp"

ProcessMemory::ProcessMemory(DWORD Pid)
{
	this->Pid = Pid;
	this->pMemorySource = new UsermodeMemory(Pid);
}

ProcessMemory::~ProcessMemory()
{
}

//
// Functions
//
template<typename T>
T ProcessMemory::ReadMemory(DWORD_PTR StartAddress)
{
	return reinterpret_cast<T>(this->pMemorySource->ReadMemory(StartAddress, sizeof(T)));
}

PVOID ProcessMemory::ReadMemory(DWORD_PTR StartAddress, SIZE_T Size)
{
	return this->pMemorySource->ReadMemory(StartAddress, Size);
}

//
// Getters
//
DWORD_PTR ProcessMemory::GetBaseAddress()
{
	return pMemorySource->GetBaseAddress();
}

//
// Checks
//
BOOL ProcessMemory::IsValid()
{
	return pMemorySource != nullptr;
}