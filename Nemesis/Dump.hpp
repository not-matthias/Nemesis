#pragma once

#include "ProcessMemory.hpp"

class Dump
{
private:
	DWORD Pid;
	std::string FileName;

public:
	Dump(DWORD Pid, std::string FileName);
	~Dump();

	BOOL DumpProcess();
};

