#include "DumpUtils.hpp"

BOOL StandardDump(DWORD Pid, std::string FileName)
{
	//
	// Create the classes
	//
	Dump Dump(24540, FileName);
	
	//
	// Dump it
	//
	return Dump.DumpProcess();
}

BOOL CustomDump(DWORD Pid, std::string FileName, DUMP_OPTIONS DumpOptions)
{
	//
	// Dump the process
	//
	ProcessMemory ProcessMemory(Pid);

	PEFile PEFile(&ProcessMemory);
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