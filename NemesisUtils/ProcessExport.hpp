#pragma once

#include <Windows.h>

struct Section
{
};

struct Memory
{
};

struct Module
{
};

struct Process
{
};

struct ProcessList
{
	Process processes[256];
};

auto GetProcessListExport(ProcessList * process_list) -> VOID;
