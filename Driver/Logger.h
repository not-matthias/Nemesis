#pragma once

#include <stdarg.h>

#define DEBUG

//
// Only print if DEBUG defined 
//
#ifdef DEBUG

VOID Log(PCSTR Format, ...)
{
	va_list args;

	//
	// Check the format
	//
	if (!Format)
		return;

	//
	// Initialize the variable list
	//
	va_start(args, Format);

	//
	// Print it
	// 
	DbgPrintEx(0, 0, Format, args);

	//
	// Stop useing the variable list
	//
	va_end(args);
}

#else

VOID Log(PCSTR Format, ...)
{
	return;
}

#endif