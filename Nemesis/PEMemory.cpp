#include "PEMemory.hpp"

PEMemory::PEMemory(ProcessMemory * pProcessMemory, DWORD_PTR StartAddress, DWORD Size)
{
	this->pProcessMemory = pProcessMemory;
	this->StartAddress = StartAddress;
	this->Size = Size;
}

PEMemory::~PEMemory()
{
	if (Buffer != nullptr)
	{
		delete Buffer;
	}
}

BOOL PEMemory::Initialize()
{
	//
	// Get the memory
	//
	Buffer = pProcessMemory->ReadMemory(StartAddress, Size);

	//
	// Check if valid
	//
	if (Buffer == nullptr)
	{
		return FALSE;
	}

	return TRUE;
}
