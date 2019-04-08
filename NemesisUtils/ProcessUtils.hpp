#pragma once

#include "ProcessExport.hpp"

#pragma comment(lib,"ntdll.lib")

class ProcessUtils
{
public:
	static auto GetProcessList() -> ProcessList*;
};
