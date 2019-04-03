#include "Dump.hpp"

#include "Module.hpp"
#include "FileWriter.hpp"

auto Dump::DumpProcess() const -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory ProcessMemory(Pid);
	if (!ProcessMemory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the pe file
	//
	Module PEFile(&ProcessMemory);
	if (!PEFile.Initialize())
	{
		return FALSE;
	}

	PEFile.SetFileAlignment();
	PEFile.AlignSectionHeaders();
	PEFile.FixHeader();
	PEFile.RemoveIat();

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
