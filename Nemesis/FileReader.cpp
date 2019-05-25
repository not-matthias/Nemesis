#include "stdafx.h"

#include "FileReader.hpp"
#include "Logger.hpp"

FileReader::FileReader(std::string path) : path(std::move(path))
{
}

FileReader::~FileReader() = default;


auto FileReader::Read(const LONG offset, const DWORD size) -> PVOID
{
	Logger::Log("Reading from the file '%s'.", path.data());

	//
	// Create the file
	//
	file_handle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return nullptr;
	}

	//
	// Set the file pointer
	//
	if (SetFilePointer(file_handle, offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		return nullptr;
	}

	//
	// Read from file
	//
	DWORD number_of_bytes_read = 0;
	const auto buffer = new BYTE[size];
	if (!ReadFile(file_handle, buffer, size, &number_of_bytes_read, nullptr))
	{
		delete[] buffer;
		return nullptr;
	}

	return buffer;
}
