#pragma once

#include <Windows.h>

struct Section
{
	/**
	 * \brief The section header struct.
	 */
	std::shared_ptr<IMAGE_SECTION_HEADER> section_header;

	/**
	 * \brief The memory of the section.
	 */
	std::shared_ptr<BYTE> buffer;

	/**
	 * \brief The size of the section.
	 */
	DWORD buffer_size;

	/**
	 * \brief The initial size of the section.
	 */
	DWORD initial_size;
};
