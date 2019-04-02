#pragma once

#include "Dump.hpp"
#include "FileWriter.hpp"
#include "PEFile.hpp"

#include <iostream>
#include <Windows.h>

// TODO: Implement config
typedef struct DUMP_OPTIONS
{

};

// 
// Dumps the main module (e.g. process.exe)
// 
BOOL StandardDump(DWORD Pid, LPCSTR FileName);

//
// Dumps a specific module (e.g. kernel32.dll)
//
BOOL DumpModule(DWORD Pid, DWORD_PTR BaseAddress, LPCSTR FileName);

//
// Dumps a specific memory region
//
BOOL DumpMemory(DWORD Pid, DWORD_PTR BaseAddress, DWORD Size, LPCSTR FileName);

BOOL CustomDump(DWORD Pid, LPCSTR FileName, DUMP_OPTIONS DumpOptions);