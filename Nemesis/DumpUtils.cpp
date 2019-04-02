#include "DumpUtils.hpp"

BOOL StandardDump(DWORD Pid, LPCSTR FileName)
{
	//
	// Create the classes
	//
	Dump Dump(Pid, FileName);

	//
	// Dump it
	//
	if (Dump.DumpProcess())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL DumpModule(DWORD Pid, DWORD_PTR BaseAddress, LPCSTR FileName)
{
	//
	// Create the memory wrapper
	//
	ProcessMemory ProcessMemory(Pid);
	if (!ProcessMemory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the pe file
	//
	PEFile PEFile(&ProcessMemory, BaseAddress);
	if (!PEFile.Initialize())
	{
		return FALSE;
	}

	PEFile.SetFileAlignment();
	PEFile.AlignSectionHeaders();
	PEFile.FixPEHeader();
	PEFile.RemoveIAT();

	//
	// Write to file
	//
	FileWriter FileWriter(FileName);
	if (FileWriter.WriteToFile(&PEFile))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL DumpMemory(DWORD Pid, DWORD_PTR StartAddress, DWORD Size, LPCSTR FileName)
{
	//
	// Create the memory wrapper
	//
	ProcessMemory ProcessMemory(Pid);
	if (!ProcessMemory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the memory
	//
	PEMemory PEMemory(&ProcessMemory, StartAddress, Size);
	if (!PEMemory.Initialize())
	{
		return FALSE;
	}

	//
	// Write to file
	//
	FileWriter FileWriter(FileName);
	if (FileWriter.WriteToFile(&PEMemory))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}