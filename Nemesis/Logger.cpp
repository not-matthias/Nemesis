#include "Logger.hpp"

#include <cstdio>

std::string Logger::prefix = "[Nemesis] ";


auto Logger::Log(std::wstring& format, ...) -> void
{
	if (format.empty())
		return;

	//
	// Insert the prefix
	//
	std::wstring wprefix;
	wprefix.assign(prefix.begin(), prefix.end());
	format.insert(0, wprefix);

	//
	// Insert new line
	//
	format.append(L"\n");

	//
	// Print it
	//
	va_list va_alist;
	va_start(va_alist, format);
	vwprintf(format.data(), va_alist);
	va_end(va_alist);
}

auto Logger::Log(std::string &format, ...) -> void
{
	if (format.empty())
		return;

	//
	// Insert the prefix
	//
	format.insert(0, prefix);

	//
	// Insert new line
	//
	format.append("\n");

	//
	// Print it
	//
	va_list va_alist;
	va_start(va_alist, format.data());
	vprintf(format.data(), va_alist);
	va_end(va_alist);
}
