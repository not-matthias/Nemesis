#include <iostream>
#include <Windows.h>

#include "DumpUtils.hpp"

int main()
{
	DumpModule(18396, 0x7ff974200000, "D:/win32u.dll");
	//Dump Dump(18396, "D:/dump.exe");
	//Dump.DumpProcess();


	std::cin.get();

	return TRUE;
}