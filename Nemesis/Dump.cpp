#include "Dump.hpp"

#include <iostream>
#include "PEFile.hpp"
#include "FileWriter.hpp"

Dump::Dump(DWORD Pid, std::string FileName)
{
	this->Pid = Pid;
	this->FileName = FileName;
}

Dump::~Dump()
{
}

BOOL Dump::DumpProcess()
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
