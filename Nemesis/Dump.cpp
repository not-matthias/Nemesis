#include "Dump.hpp"

#include <iostream>
#include "PEFile.hpp"
#include "FileWriter.h"

Dump::Dump(DWORD Pid)
{
	std::cout << "Dumping the process with the pid: " << Pid << std::endl;

	//
	// Dump the process
	//
	ProcessMemory ProcessMemory(Pid);

	PEFile PEFile(&ProcessMemory);
	PEFile.ReadPEHeader();
	PEFile.SetSections();

	std::cout << "Sections: " << PEFile.GetSectionCount() << std::endl;

	//
	// Write to file
	//
	FileWriter FileWriter(&PEFile);
	FileWriter.WriteToFile("D:/dump.exe");

}

Dump::~Dump()
{
}
