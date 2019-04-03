#pragma once

#include <Windows.h>

// 
// Dumps the main Module (e.g. process.exe)
// 
BOOL DumpMainModule(DWORD process_id, LPCSTR file_name);

//
// Dumps a specific Module (e.g. kernel32.dll)
//
auto DumpModule(DWORD process_id, DWORD_PTR base_address, LPCSTR file_name) -> BOOL;

//
// Dumps a specific Memory region
//
auto DumpMemory(DWORD process_id, DWORD_PTR start_address, DWORD size, LPCSTR file_name) -> BOOL;
