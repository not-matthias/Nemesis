#include <Windows.h>

#include "Dump.hpp"

int main()
{
	Dump *pDump = new Dump(21308);

	std::cin.get();

	return EXIT_SUCCESS;
}