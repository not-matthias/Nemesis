#include "Logger.hpp"

#include <cstdio>

auto logger::Log(const WCHAR * format, ...) -> void
{
	static WCHAR buffer[300];

	if (!format)
		return;

	va_list va_alist;
	va_start(va_alist, format);
	_vsnwprintf_s(buffer, _countof(buffer) - 1, format, va_alist);
	va_end(va_alist);
}

auto logger::Log(const CHAR * format, ...) -> void
{
	static char buffer[300];

	if (!format)
		return;

	va_list va_alist;
	va_start(va_alist, format);
	_vsnprintf_s(buffer, _countof(buffer) - 1, format, va_alist);
	va_end(va_alist);
}
