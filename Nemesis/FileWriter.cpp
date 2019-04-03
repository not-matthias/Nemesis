#include "FileWriter.hpp"
#include <utility>

FileWriter::FileWriter(std::string file_name) : file_name(std::move(file_name))
{
}

FileWriter::~FileWriter() = default;

auto FileWriter::WriteToFile(Module * module) -> BOOL
{
	//
	// Some checks
	//
	if (module->GetSectionCount() != module->sections.size())
	{
		return FALSE;
	}


	//
	// Create the file
	//
	file_handle = CreateFile(file_name.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}


	//
	// DOS Header
	//
	DWORD file_offset = 0, write_size = sizeof(IMAGE_DOS_HEADER);
	if (!WriteMemoryToFile(file_offset, write_size, module->dos_header))
	{
		return FALSE;
	}
	file_offset += write_size;


	//
	// Stubs
	//
	if (module->dos_stub_size && module->dos_stub)
	{
		write_size = module->dos_stub_size;
		if (!WriteMemoryToFile(file_offset, write_size, module->dos_stub))
		{
			return FALSE;
		}
		file_offset += write_size;
	}


	//
	// PE Header
	//
	if (module->Is32Bit())
	{
		write_size = sizeof(IMAGE_NT_HEADERS32);

		if (!WriteMemoryToFile(file_offset, write_size, module->nt_header32))
		{
			return FALSE;
		}

		file_offset += write_size;
	}
	else
	{
		write_size = sizeof(IMAGE_NT_HEADERS64);

		if (!WriteMemoryToFile(file_offset, write_size, module->nt_header64))
		{
			return FALSE;
		}

		file_offset += write_size;
	}

	// 
	// Section Header
	// 
	write_size = sizeof(IMAGE_SECTION_HEADER);
	for (WORD i = 0; i < module->GetSectionCount(); i++)
	{
		if (!WriteMemoryToFile(file_offset, write_size, &module->sections[i].section_header))
		{
			return FALSE;
		}

		file_offset += write_size;
	}


	//
	// Sections
	//
	for (WORD i = 0; i < module->GetSectionCount(); i++)
	{
		// 
		// Raw data not found
		//
		if (module->sections[i].section_header.PointerToRawData == NULL)
			continue;

		//
		// PointerToRawData > dwFileOffset => Padding needed
		//
		if (module->sections[i].section_header.PointerToRawData > file_offset)
		{
			//
			// Calculate the padding
			//
			write_size = module->sections[i].section_header.PointerToRawData - file_offset;

			//
			// Write the padding
			//
			if (!WriteZeroMemoryToFile(file_offset, write_size))
			{
				return FALSE;
			}

			file_offset += write_size;
		}

		//
		// Write the section data
		//
		write_size = module->sections[i].data_size;

		if (!WriteMemoryToFile(module->sections[i].section_header.PointerToRawData, write_size, module->sections[i].content))
		{
			return FALSE;
		}

		file_offset += write_size;


		//
		// DataSize < SizeOfRawData => Padding needed
		//
		if (module->sections[i].data_size < module->sections[i].section_header.SizeOfRawData)
		{
			//
			// Calculate the padding
			//
			write_size = module->sections[i].section_header.SizeOfRawData - module->sections[i].data_size;

			//
			// Write the padding
			//
			if (!WriteZeroMemoryToFile(file_offset, write_size))
			{
				return FALSE;
			}

			file_offset += write_size;
		}
	}


	//
	// TODO: Add overlay
	//
	//if (overlaySize && overlayData)
	//{
	//	dwWriteSize = overlaySize;
	//	if (!ProcessAccessHelp::writeMemoryToFile(hFile, dwFileOffset, dwWriteSize, overlayData))
	//	{
	//		retValue = false;
	//	}
	//	dwFileOffset += dwWriteSize;
	//}


	//
	// Set EOL
	//
	SetEndOfFile(file_handle);


	//
	// Close the handle
	//
	if (file_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_handle);
	}

	return TRUE;
}

auto FileWriter::WriteToFile(Memory * memory) -> BOOL
{
	//
	// Create the file
	//
	file_handle = CreateFile(file_name.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	//
	// Write the memory_buffer to the file
	//
	if (WriteMemoryToFile(0, memory->memory_size, memory->memory_buffer))
	{
		return FALSE;
	}

	//
	// Set EOL
	//
	SetEndOfFile(file_handle);


	//
	// Close the handle
	//
	if (file_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_handle);
	}

	return TRUE;
}

auto FileWriter::WriteMemoryToFile(const LONG offset, const DWORD size, const LPCVOID buffer) const -> BOOL
{
	DWORD lpNumberOfBytesWritten = 0;

	//
	// Some checks
	//
	if (file_handle == INVALID_HANDLE_VALUE || buffer == nullptr)
	{
		return FALSE;
	}

	//
	// Set the file pointer
	//
	if (SetFilePointer(file_handle, offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		return FALSE;
	}

	//
	// Write to the file
	//
	if (!WriteFile(file_handle, buffer, size, &lpNumberOfBytesWritten, nullptr))
	{
		return FALSE;
	}

	return TRUE;
}

auto FileWriter::WriteZeroMemoryToFile(const LONG offset, const DWORD size) const -> BOOL
{
	const auto buffer = calloc(size, 1);

	//
	// Check the memory_buffer
	//
	if (!buffer)
	{
		return FALSE;
	}

	//
	// Write to file
	//
	if (!WriteMemoryToFile(offset, size, buffer))
	{
		return FALSE;
	}

	//
	// Free Memory
	//
	free(buffer);

	return TRUE;
}
