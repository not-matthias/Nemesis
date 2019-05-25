#include <Windows.h>
#include <iostream>

#include "FileReader.hpp"
#include <Psapi.h>
#include "Logger.hpp"
#include "ProcessUtils.hpp"


int main()
{
	std::cout << "Name: " << ProcessUtils::GetFilePath(22380) << std::endl;

	FileReader file_reader("D:/test.txt");

	auto buffer = file_reader.ReadFromFile(-10, 0x1);

	std::cin.get();

	return EXIT_SUCCESS;
}
