#include <iostream>
#include <Windows.h>

#include "DumpUtils.hpp"

int main()
{
	//DumpModule(18396, static_cast<DWORD_PTR>(0x7ff974200000), "D:/win32u.dll");

	DumpProcess(71940, "D:/dump.exe");


	std::cin.get();

	return TRUE;
}
