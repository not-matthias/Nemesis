#pragma once

#include <stdio.h>
#include <Windows.h>

namespace Logger
{
	void Log(const WCHAR * format, ...);
	void Log(const CHAR * format, ...);
};

