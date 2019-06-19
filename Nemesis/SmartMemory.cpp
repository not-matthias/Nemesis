#include "stdafx.h"

#include "SmartMemory.hpp"

SmartMemory::SmartMemory(SIZE_T size) : buffer(size, 0)
{
}

auto SmartMemory::get() -> BYTE*
{
	return &buffer[0];
}
