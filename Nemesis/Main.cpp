#include <iostream>
#include <Windows.h>

#include "DumpUtils.hpp"

int main()
{
	Dump Dump(26020, "D:/dump.exe");
	Dump.DumpProcess();


	std::cin.get();

	return TRUE;
}