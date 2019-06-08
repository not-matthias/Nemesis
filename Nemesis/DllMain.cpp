#include "stdafx.h"

#include <Windows.h>

BOOL WINAPI DllMain()
{
	return TRUE;
}

#include "ProcessUtils.hpp"
#include "DumpExport.hpp"

int main()
{
	const auto module_list = ProcessUtils::GetModuleList(12340);
	const auto manual_module_list = ProcessUtils::GetModuleListManually(12340);

	DumpProcessExport(12340, "D:/notepad.exe");


	std::cin.get();

	return EXIT_SUCCESS;
}