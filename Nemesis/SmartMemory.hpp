#pragma once

#include <Windows.h>

struct MemoryDisposer
{
	void operator()(const BYTE * buffer) const
	{
		delete[] buffer;
	}
};

class SmartMemory
{
public:

	/**
	 * \brief The allocated memory.
	 */
	std::vector<BYTE> buffer;

	/**
	 * \brief Creates a new memory buffer.
	 * \param size The size of the buffer.
	 */
	SmartMemory(SIZE_T size);
};
