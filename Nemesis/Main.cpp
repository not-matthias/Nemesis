#include <iostream>
#include <Windows.h>

#include "DumpExport.hpp"
#include "MemorySourceExport.h"

int main()
{
	//DumpModule(18396, static_cast<DWORD_PTR>(0x7ff974200000), "D:/win32u.dll");

	auto memory_sources = GetMemorySources();

	std::cout << DumpProcess(92200, "D:/dump_1.exe") << std::endl;
	SetMemorySource("kernel_mode");
	std::cout << DumpProcess(92200, "D:/dump_2.exe") << std::endl;


	std::cin.get();

	return TRUE;
}
