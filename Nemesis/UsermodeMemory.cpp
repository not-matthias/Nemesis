#include "UsermodeMemory.hpp"

UsermodeMemory::UsermodeMemory(DWORD Pid) : IMemorySource(Pid)
{
	this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pid);
	if (this->hProcess == INVALID_HANDLE_VALUE)
	{
		Logger::Log("Failed to open process.");
	}
}

UsermodeMemory::~UsermodeMemory()
{
	if (this->hProcess != INVALID_HANDLE_VALUE)
		CloseHandle(this->hProcess);
}

PVOID UsermodeMemory::ReadMemory(DWORD_PTR StartAddress, SIZE_T Size)
{
	if (this->hProcess == INVALID_HANDLE_VALUE)
		return nullptr;

	BYTE *Buffer = new BYTE[Size];
	SIZE_T BytesRead;
	DWORD OldProtect;

	// 
	// ReadProcessMemory
	// 
	if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(StartAddress), Buffer, Size, &BytesRead))
	{
		std::cout << "[1] Failed to read process memory." << std::endl;

		//
		// RPM Failed - Disable page protection
		//
		if (!VirtualProtectEx(hProcess, reinterpret_cast<LPVOID>(StartAddress), Size, PAGE_READWRITE, &OldProtect))
		{
			std::cout << "[2] Failed to VirtualProtectEx" << std::endl;
			return nullptr;
		}

		// 
		// ReadProcessMemory
		// 
		if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(StartAddress), Buffer, Size, &BytesRead))
		{
			std::cout << "[3] Failed to read process memory." << std::endl;
		}

		VirtualProtectEx(hProcess, (LPVOID)StartAddress, Size, OldProtect, &OldProtect);
	}

	return Buffer;
}

DWORD_PTR UsermodeMemory::GetBaseAddress()
{
	//HMODULE hModules[1024];
	TCHAR szFileName[MAX_PATH];
	TCHAR szModuleName[MAX_PATH];
	HMODULE *hModules = NULL;
	DWORD cbNeeded;
	DWORD cModules;
	DWORD_PTR BaseAddress = NULL;

	//
	// Set the hModules size
	//
	EnumProcessModules(hProcess, hModules, 0, &cModules);
	hModules = new HMODULE[cModules / sizeof(HMODULE)];

	//
	// Get the module name
	//
	GetModuleBaseName(hProcess, NULL, szFileName, sizeof(szFileName));

	//
	// Get the base address
	//
	if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			std::string FileName(szFileName);

			if (GetModuleBaseName(hProcess, hModules[i], szModuleName, sizeof(szModuleName))) {
				if (FileName.compare(szModuleName) == 0) {
					BaseAddress = reinterpret_cast<DWORD_PTR>(hModules[i]);
					break;
				}
			}

		}
	}

	delete[] hModules;

	return BaseAddress;
}