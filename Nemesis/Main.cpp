#include <iostream>
#include <Windows.h>

#include "DumpExport.hpp"
#include "MemorySourceExport.h"

int main()
{
	//DumpModuleExport(18396, static_cast<DWORD_PTR>(0x7ff974200000), "D:/win32u.dll");

	//std::cout << DumpProcessExport(1440, "D:\\dump_1.exe") << std::endl;
	//std::cout << DumpProcessExport(1440, "D:\\dump_2.exe") << std::endl;


	std::cin.get();

	return TRUE;
}
