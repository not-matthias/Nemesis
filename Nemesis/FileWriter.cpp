#include "stdafx.h"

#include "FileWriter.hpp"
#include "Logger.hpp"

FileWriter::FileWriter(std::wstring file_name) : file_name(std::move(file_name))
{
}

auto FileWriter::WriteToFile(Module * module) -> BOOL
{
	Logger::Log("Writing to the file '%s'.", file_name.data());

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
	file_handle = SmartHandle(CreateFile(file_name.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
	if (!file_handle.IsValid())
	{
		return FALSE;
	}


	//
	// DOS Header
	//
	DWORD file_offset = 0, write_size = sizeof(IMAGE_DOS_HEADER);
	if (!WriteMemoryToFile(file_offset, write_size, std::reinterpret_pointer_cast<BYTE>(module->dos_header)))
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

		if (!WriteMemoryToFile(file_offset, write_size, std::reinterpret_pointer_cast<BYTE>(module->nt_header32)))
		{
			return FALSE;
		}

		file_offset += write_size;
	}
	else
	{
		write_size = sizeof(IMAGE_NT_HEADERS64);

		if (!WriteMemoryToFile(file_offset, write_size, std::reinterpret_pointer_cast<BYTE>(module->nt_header64)))
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
		// maybe & needed
		if (!WriteMemoryToFile(file_offset, write_size, std::reinterpret_pointer_cast<BYTE>(module->sections[i].section_header)))
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
		if (module->sections[i].section_header->PointerToRawData == NULL)
			continue;

		//
		// PointerToRawData > dwFileOffset => Padding needed
		//
		if (module->sections[i].section_header->PointerToRawData > file_offset)
		{
			//
			// Calculate the padding
			//
			write_size = module->sections[i].section_header->PointerToRawData - file_offset;

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
		write_size = module->sections[i].buffer_size;

		if (!WriteMemoryToFile(module->sections[i].section_header->PointerToRawData, write_size, module->sections[i].buffer))
		{
			return FALSE;
		}

		file_offset += write_size;


		//
		// DataSize < SizeOfRawData => Padding needed
		//
		if (module->sections[i].buffer_size < module->sections[i].section_header->SizeOfRawData)
		{
			//
			// Calculate the padding
			//
			write_size = module->sections[i].section_header->SizeOfRawData - module->sections[i].buffer_size;

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
	SetEndOfFile(file_handle.Get());

	return TRUE;
}

auto FileWriter::WriteToFile(MemoryElement * memory) -> BOOL
{
	//
	// Create the file
	//
	file_handle = SmartHandle(CreateFile(file_name.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
	if (!file_handle.IsValid())
	{
		return FALSE;
	}

	//
	// Write the memory_buffer to the file
	//
	if (!WriteMemoryToFile(0, memory->memory_size, std::reinterpret_pointer_cast<BYTE>(memory->memory_buffer)))
	{
		return FALSE;
	}

	//
	// Set EOL
	//
	SetEndOfFile(file_handle.Get());

	return TRUE;
}

auto FileWriter::WriteMemoryToFile(const LONG offset, const DWORD size, const std::shared_ptr<BYTE> buffer) const -> BOOL
{
	DWORD number_of_bytes_written = 0;

	//
	// Some checks
	//
	if (!file_handle.IsValid() || !buffer)
	{
		return FALSE;
	}

	//
	// Set the file pointer
	//
	if (SetFilePointer(file_handle.Get(), offset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		return FALSE;
	}

	//
	// Write to the file
	//
	if (!WriteFile(file_handle.Get(), buffer.get(), size, &number_of_bytes_written, nullptr))
	{
		return FALSE;
	}

	return TRUE;
}

auto FileWriter::WriteZeroMemoryToFile(const LONG offset, const DWORD size) const -> BOOL
{
	const std::shared_ptr<BYTE> buffer(new BYTE[size]{0}, [](const BYTE * memory) { delete[] memory; });

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

	return TRUE;
}
