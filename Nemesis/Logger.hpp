#pragma once

#include <Windows.h>

namespace logger
{
	/**
	 * \brief Prints the specified wide string.
	 * \param format the format string
	 * \param ... the additional parameters
	 */
	auto Log(const WCHAR * format, ...) -> void;

	/**
	 * \brief Prints the specified string.
	 * \param format the format string
	 * \param ... the additional parameters
	 */
	auto Log(const CHAR * format, ...) -> void;
};
