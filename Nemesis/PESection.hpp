#pragma once

#include <Windows.h>

class PESection
{
public:
	IMAGE_SECTION_HEADER SectionHeader;
	BYTE *pData;
	DWORD DataSize;
	DWORD NormalSize;

	PESection();
	~PESection();
};

