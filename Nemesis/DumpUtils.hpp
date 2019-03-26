#pragma once

#include "Dump.hpp"
#include "FileWriter.h"
#include "PEFile.hpp"

#include <iostream>
#include <Windows.h>

// TODO: Implement config
typedef struct DUMP_OPTIONS
{

};


// Standard config
BOOL StandardDump(DWORD Pid, std::string FileName);

BOOL CustomDump(DWORD Pid, std::string FileName, DUMP_OPTIONS DumpOptions);