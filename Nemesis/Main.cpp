#include <iostream>
#include <Windows.h>

#include "DumpUtils.hpp"

int main()
{
	//DumpModule(18396, 0x7ff974200000, "D:/win32u.dll");
	
	DumpMemory(18396, static_cast<DWORD_PTR>(0x7FF977391000), 0x117000, "D:/ntdll_text.bin");

	//Dump Dump(18396, "D:/dump.exe");
	//Dump.DumpProcess();


	std::cin.get();

	return TRUE;
}
