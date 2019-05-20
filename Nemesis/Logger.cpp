#include "Logger.hpp"

#include <cstdio>

std::string Logger::prefix = "[Nemesis] ";

auto Logger::Log(std::wstring format, ...) -> VOID
{
	if (format.empty())
		return;

	//
	// Insert the prefix
	//
	std::wstring wide_prefix;
	wide_prefix.assign(prefix.begin(), prefix.end());
	format.insert(0, wide_prefix);

	//
	// Insert new line
	//
	format.append(L"\n");

	//
	// Print it
	//
	va_list arg_list;
	va_start(arg_list, format);
	vwprintf(format.data(), arg_list);
	va_end(arg_list);
}

auto Logger::Log(std::string format, ...) -> VOID
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
	va_list arg_list;
	va_start(arg_list, format);
	vprintf(format.data(), arg_list);
	va_end(arg_list);
}
