#pragma once

#include <Windows.h>

class PESection
{
public:
	IMAGE_SECTION_HEADER SectionHeader;
	PVOID Content;
	DWORD DataSize;
	DWORD InitialSize;

	PESection();
	~PESection();
};

