#pragma once

#include <Windows.h>

class Section
{
public:
	IMAGE_SECTION_HEADER section_header_;
	BYTE *content_;
	DWORD data_size_;
	DWORD initial_size_;

	Section();
	~Section();
};

