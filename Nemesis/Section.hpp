#pragma once

#include <Windows.h>

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
	BYTE *content;

	/**
	 * \brief The size of the section.
	 */
	DWORD data_size;

	/**
	 * \brief The initial size of the section.
	 */
	DWORD initial_size;


	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Initializes the variables.
	 */
	Section();
};
