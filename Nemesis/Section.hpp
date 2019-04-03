#pragma once

#include <Windows.h>

// TODO: Use struct instead
class Section
{
public:
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The section header struct.
	 */
	IMAGE_SECTION_HEADER section_header{};

	/**
	 * \brief The memory of the section.
	 */
	BYTE *content = nullptr;

	/**
	 * \brief The size of the section.
	 */
	DWORD data_size = NULL;

	/**
	 * \brief The initial size of the section.
	 */
	DWORD initial_size = NULL;
};
