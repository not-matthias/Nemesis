#pragma once

#include <stdarg.h>

#define DEBUG

//
// Only print if DEBUG defined 
//
#ifdef DEBUG

VOID Log(const PCSTR format, ...)
{
	va_list args;

	//
	// Check the format
	//
	if (!format)
		return;

	//
	// Initialize the variable list
	//
	va_start(args, format);

	//
	// Print it
	// 
	DbgPrint(format, args);

	//
	// Stop using the variable list
	//
	va_end(args);
}

#else

VOID Log(PCSTR Format, ...)
{
	return;
}

#endif