#pragma once

#include <stdarg.h>

#define DEBUG

//
// Variables
//
PCSTR Prefix = "[Nemesis] ";

//
// Only print if DEBUG defined 
//
#ifdef DEBUG

VOID Log(PCSTR Format, ...)
{
	va_list args;
	PSTR OutputFormat = "";

	//
	// Check the format
	//
	if (!Format)
		return;

	// 
	// Craft the output format
	// 
	strcat(OutputFormat, Prefix);
	strcat(OutputFormat, Format);

	//
	// Initialize the variable list
	//
	va_start(args, Format);

	//
	// Print it
	// 
	DbgPrint(Format, args);

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