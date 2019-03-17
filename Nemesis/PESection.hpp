#pragma once

#include <Windows.h>

class PESection
{
public:
	PIMAGE_SECTION_HEADER pSectionHeader;
	BYTE *pData;
	DWORD pDataSize;
	DWORD NormalSize;

	PESection();
	~PESection();
};

