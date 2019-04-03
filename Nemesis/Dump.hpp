#pragma once

#include "ProcessMemory.hpp"
#include <string>

class Dump
{
	DWORD Pid;
	std::string FileName;

public:
	Dump(const DWORD Pid, std::string FileName) : Pid(Pid), FileName(std::move(FileName)) {}
	~Dump() = default;

	BOOL DumpProcess() const;
};
