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
BOOL StandardDump(DWORD Pid, LPCSTR FileName);

BOOL CustomDump(DWORD Pid, LPCSTR FileName, DUMP_OPTIONS DumpOptions);