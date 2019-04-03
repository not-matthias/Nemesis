#pragma once

#include <Windows.h>

class Section
{
public:
	IMAGE_SECTION_HEADER section_header{};
	BYTE *content;
	DWORD data_size;
	DWORD initial_size;

	Section();
	~Section();
};

