#include "UsermodeMemorySource.hpp"

UsermodeMemorySource::UsermodeMemorySource(DWORD Pid) : IMemorySource(Pid)
{
	this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
	if (this->hProcess == INVALID_HANDLE_VALUE)
	{
		Logger::Log("Failed to open process.");
	}
}

UsermodeMemorySource::~UsermodeMemorySource()
{
	if (this->hProcess != INVALID_HANDLE_VALUE)
		CloseHandle(this->hProcess);
}

BOOL UsermodeMemorySource::ReadMemory(DWORD_PTR StartAddress, DWORD_PTR EndAddress)
{
	return FALSE;
}
