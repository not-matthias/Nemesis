#pragma once

#include "Module.hpp"
#include "Memory.hpp"
#include <string>

class FileWriter
{
	std::string file_name;
	HANDLE file_handle = INVALID_HANDLE_VALUE;

public:
	explicit FileWriter(std::string file_name);
	~FileWriter();

	auto WriteToFile(Module* module) -> BOOL;
	auto WriteToFile(Memory* memory) -> BOOL;

	auto WriteMemoryToFile(LONG offset, DWORD size, LPCVOID buffer) const -> BOOL;
	auto WriteZeroMemoryToFile(LONG offset, DWORD size) const -> BOOL;
};
