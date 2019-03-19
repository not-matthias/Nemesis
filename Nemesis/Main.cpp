#include <Windows.h>

#include "Dump.hpp"

int main()
{
	Dump *pDump = new Dump(5652);

	std::cin.get();

	return EXIT_SUCCESS;
}