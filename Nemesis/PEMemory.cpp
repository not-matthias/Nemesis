#include "Memory.hpp"

Memory::Memory(ProcessMemory * pProcessMemory, DWORD_PTR StartAddress, DWORD Size)
{
	this->pProcessMemory = pProcessMemory;
	this->StartAddress = StartAddress;
	this->Size = Size;
}

Memory::~Memory()
{
	if (Buffer != nullptr)
	{
		delete Buffer;
	}
}

BOOL Memory::Initialize()
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
