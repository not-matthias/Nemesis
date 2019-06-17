#include "stdafx.h"

#include "FileReader.hpp"
#include "Logger.hpp"

FileReader::FileReader(std::wstring path) : path(std::move(path))
{
}

auto FileReader::Read(const LONG offset, const DWORD size) -> std::shared_ptr<BYTE>
{
	Logger::Log("Reading from the file '%s'.", path.data());

	//
	// Create the file
	//
	file_handle = SafeHandle(CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
	if (!file_handle.IsValid())
	{
		return nullptr;
	}

	//
	// Set the file pointer
	//
	if (SetFilePointer(file_handle.Get(), offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		return nullptr;
	}

	//
	// Read from file
	//
	const auto buffer = std::shared_ptr<BYTE>(new BYTE[size], [](const BYTE * memory) { delete[] memory; });
	if (!ReadFile(file_handle.Get(), buffer.get(), size, nullptr, nullptr))
	{
		return nullptr;
	}

	return buffer;
}
