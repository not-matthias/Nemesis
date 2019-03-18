#include "FileWriter.h"

FileWriter::FileWriter(PEFile *pPEFile)
{
	this->pPEFile = pPEFile;
}

FileWriter::~FileWriter()
{
	delete pPEFile;
}

BOOL FileWriter::WriteToFile(std::string FileName)
{
	DWORD dwFileOffset = 0, dwWriteSize = 0;

	//
	// Some checks
	//
	if (pPEFile->GetSectionCount() != pPEFile->Sections.size())
	{
		return FALSE;
	}


	//
	// Create the file
	//
	hFile = CreateFile(FileName.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	

	//
	// DOS Header
	//
	dwWriteSize = sizeof(IMAGE_DOS_HEADER);
	if (!WriteMemoryToFile(dwFileOffset, dwWriteSize, pPEFile->pDosHeader))
	{
		return FALSE;
	}
	dwFileOffset += dwWriteSize;


	//
	// Stubs
	//
	if (pPEFile->DosStubSize && pPEFile->pDosStub)
	{
		dwWriteSize = pPEFile->DosStubSize;
		if (!WriteMemoryToFile(dwFileOffset, dwWriteSize, pPEFile->pDosStub))
		{
			return FALSE;
		}
		dwFileOffset += dwWriteSize;
	}


	//
	// PE Header
	//
	if (pPEFile->IsPE32())
	{
		dwWriteSize = sizeof(IMAGE_NT_HEADERS32);

		if (!WriteMemoryToFile(dwFileOffset, dwWriteSize, pPEFile->pNTHeader32))
		{
			return FALSE;
		}

		dwFileOffset += dwWriteSize;
	}
	else
	{
		dwWriteSize = sizeof(IMAGE_NT_HEADERS64); 
		
		if (!WriteMemoryToFile(dwFileOffset, dwWriteSize, pPEFile->pNTHeader64))
		{
			return FALSE;
		}

		dwFileOffset += dwWriteSize;
	}

	// 
	// Section Header
	// 
	dwWriteSize = sizeof(IMAGE_SECTION_HEADER);
	for (WORD i = 0; i < pPEFile->GetSectionCount(); i++)
	{
		if (!WriteMemoryToFile(dwFileOffset, dwWriteSize, &pPEFile->Sections[i]->SectionHeader))
		{
			return FALSE;
		}

		dwFileOffset += dwWriteSize;
	}


	//
	// Sections
	//
	for (WORD i = 0; i < pPEFile->GetSectionCount(); i++)
	{
		// 
		// Raw data not found
		//
		if (pPEFile->Sections[i]->SectionHeader.PointerToRawData == NULL)
			continue;

		//
		// PointerToRawData > dwFileOffset => Padding needed
		//
		if (pPEFile->Sections[i]->SectionHeader.PointerToRawData > dwFileOffset)
		{
			//
			// Calculate the padding
			//
			dwWriteSize = pPEFile->Sections[i]->SectionHeader.PointerToRawData - dwFileOffset;

			//
			// Write the padding
			//
			if (!WriteZeroMemoryToFile(dwFileOffset, dwWriteSize))
			{
				return FALSE;
			}

			dwFileOffset += dwWriteSize;
		}

		//
		// Write the section data
		//
		dwWriteSize = pPEFile->Sections[i]->DataSize;

		if (!WriteMemoryToFile(pPEFile->Sections[i]->SectionHeader.PointerToRawData, dwWriteSize, pPEFile->Sections[i]->pData))
		{
			return FALSE;
		}

		dwFileOffset += dwWriteSize;


		//
		// DataSize < SizeOfRawData => Padding needed
		//
		if (pPEFile->Sections[i]->DataSize < pPEFile->Sections[i]->SectionHeader.SizeOfRawData)
		{
			//
			// Calculate the padding
			//
			dwWriteSize = pPEFile->Sections[i]->SectionHeader.SizeOfRawData - pPEFile->Sections[i]->DataSize;

			//
			// Write the padding
			//
			if (!WriteZeroMemoryToFile(dwFileOffset, dwWriteSize))
			{
				return FALSE;
			}

			dwFileOffset += dwWriteSize;
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
	SetEndOfFile(hFile);


	//
	// Close the handle
	//
	if (hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFile);
	}

	return TRUE;
}

BOOL FileWriter::WriteMemoryToFile(LONG Offset, DWORD Size, LPCVOID Buffer)
{
	DWORD lpNumberOfBytesWritten = 0;

	//
	// Some checks
	//
	if (hFile == INVALID_HANDLE_VALUE || Buffer == nullptr)
	{
		return FALSE;
	}

	//
	// Set the file pointer
	//
	if (SetFilePointer(hFile, Offset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
	{
		return FALSE;
	}

	//
	// Write to the file
	//
	if (!WriteFile(hFile, Buffer, Size, &lpNumberOfBytesWritten, NULL))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL FileWriter::WriteZeroMemoryToFile(LONG Offset, DWORD Size)
{
	PVOID Buffer = calloc(Size, 1);

	//
	// Check the buffer
	//
	if (!Buffer)
	{
		return FALSE;
	}

	//
	// Write to file
	//
	if (!WriteMemoryToFile(Offset, Size, Buffer))
	{
		return FALSE;
	}

	//
	// Free memory
	//
	free(Buffer);

	return TRUE;
}


