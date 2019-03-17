#include "ProcessMemory.hpp"

Memory::Memory(DWORD Pid)
{
	this->Pid = Pid;
	this->pMemorySource = new UsermodeMemorySource(Pid);
}

Memory::~Memory()
{
	delete pMemorySource;
}

BOOL Memory::ReadMemory(DWORD_PTR StartAddress, DWORD_PTR EndAddress)
{
	return FALSE;
}

//private PEFile Dump64BitPE(int processId, IMAGE_DOS_HEADER dosHeader, byte[] dosStub, IntPtr peHeaderPointer)
//{
//	IMAGE_NT_HEADERS64 peHeader = ReadProcessStruct<IMAGE_NT_HEADERS64>(processId, peHeaderPointer);
//
//	if (peHeader.IsValid)
//	{
//		return new PE64File(dosHeader, peHeader, dosStub);
//	}
//	return default(PEFile);
//}
//
//private PEFile Dump32BitPE(int processId, IMAGE_DOS_HEADER dosHeader, byte[] dosStub, IntPtr peHeaderPointer)
//{
//	IMAGE_NT_HEADERS32 peHeader = ReadProcessStruct<IMAGE_NT_HEADERS32>(processId, peHeaderPointer);
//
//	if (peHeader.IsValid)
//	{
//		return new PE32File(dosHeader, peHeader, dosStub);
//	}
//	return default(PEFile);
//}