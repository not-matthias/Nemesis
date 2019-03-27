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

BOOL CustomDump(DWORD Pid, LPCSTR FileName, DUMP_OPTIONS DumpOptions)
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
	PEFile PEFile(&ProcessMemory);
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
	FileWriter FileWriter(&PEFile);
	if (FileWriter.WriteToFile(FileName))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}