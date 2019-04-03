#pragma once

#include <Windows.h>

namespace logger
{
	auto Log(const WCHAR* format, ...) -> void;
	auto Log(const CHAR* format, ...) -> void;
};

