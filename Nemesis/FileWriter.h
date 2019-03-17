#pragma once

#include "PEFile.hpp"

class FileWriter
{
private:
	PEFile *pPEFile;

public:
	FileWriter(PEFile *pPEFile);
	~FileWriter();

	VOID WriteToFile(std::string FileName);
};

