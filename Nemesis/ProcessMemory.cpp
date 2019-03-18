#include "ProcessMemory.hpp"

ProcessMemory::ProcessMemory(DWORD Pid)
{
	this->Pid = Pid;
	this->pMemorySource = new UsermodeMemorySource(Pid);
}

ProcessMemory::~ProcessMemory()
{
	delete pMemorySource;
}

template<typename T>
T ProcessMemory::ReadMemory(DWORD_PTR StartAddress)
{
	return reinterpret_cast<T>(this->pMemorySource->ReadMemory(StartAddress, sizeof(T)));
}

PVOID ProcessMemory::ReadMemory(DWORD_PTR StartAddress, SIZE_T Size)
{
	return this->pMemorySource->ReadMemory(StartAddress, Size);
}

DWORD_PTR ProcessMemory::GetBaseAddress()
{
	return pMemorySource->GetBaseAddress();
}