#include "stdafx.h"

#include <Windows.h>

BOOL WINAPI DllMain()
{
	return TRUE;
}

#include "ProcessUtils.hpp"

int main()
{
	const auto module_list = ProcessUtils::GetModuleList(41432);
	const auto manual_module_list = ProcessUtils::GetModuleListManually(41432);

	std::cin.get();

	return EXIT_SUCCESS;
}