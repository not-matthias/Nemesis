#include "Logger.hpp"

void Logger::Log(const WCHAR * format, ...)
{
	static WCHAR buf[300];

	if (!format)
		return;

	va_list va_alist;
	va_start(va_alist, format);
	_vsnwprintf_s(buf, _countof(buf) - 1, format, va_alist);
	va_end(va_alist);

}

void Logger::Log(const CHAR * format, ...)
{
	static char buf[300];

	if (!format)
		return;

	va_list va_alist;
	va_start(va_alist, format);
	_vsnprintf_s(buf, _countof(buf) - 1, format, va_alist);
	va_end(va_alist);

}