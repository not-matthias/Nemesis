#include <Windows.h>

#include "Dump.hpp"

int main()
{
	Dump *pDump = new Dump(8524);

	std::cin.get();

	return EXIT_SUCCESS;
}