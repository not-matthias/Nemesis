#include "stdafx.h"

#include "Logger.hpp"

std::string Logger::prefix = "[Nemesis] ";

auto Logger::Log(std::wstring format, ...) -> VOID
{
	if (format.empty())
		return;

	//
	// Insert the prefix
	//
	format.insert(format.begin(), prefix.begin(), prefix.end());

	//
	// Insert new line
	//
	format.push_back('\n');

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
