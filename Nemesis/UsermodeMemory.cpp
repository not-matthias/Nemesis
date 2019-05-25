#include "stdafx.h"

#include "Logger.hpp"
#include "UsermodeMemory.hpp"

UsermodeMemory::UsermodeMemory(const DWORD process_id) : IMemorySource(process_id)
{
	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

	if (process_handle == INVALID_HANDLE_VALUE)
	{
		Logger::Log("Failed to open process.");
	}
}

UsermodeMemory::~UsermodeMemory()
{
	if (process_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(process_handle);
	}
}

auto UsermodeMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) -> PVOID
{
	if (process_handle == INVALID_HANDLE_VALUE)
		return nullptr;

	const auto buffer = new BYTE[size];
	SIZE_T bytes_read;
	DWORD old_protect;

	// 
	// ReadProcessMemory
	// 
	if (!ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(start_address), buffer, size, &bytes_read))
	{
		Logger::Log("Failed to read process memory.");

		//
		// RPM Failed - Disable page protection
		//
		if (!VirtualProtectEx(process_handle, reinterpret_cast<LPVOID>(start_address), size, PAGE_READWRITE, &old_protect))
		{
			Logger::Log("Failed to change page protection.");
			return nullptr;
		}

		// 
		// ReadProcessMemory
		// 
		if (!ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(start_address), buffer, size, &bytes_read))
		{
			Logger::Log("Failed to read process memory.");
		}

		VirtualProtectEx(process_handle, reinterpret_cast<LPVOID>(start_address), size, old_protect, &old_protect);
	}

	return buffer;
}

auto UsermodeMemory::IsValid() -> BOOL
{
	//
	// Check if handle is valid
	//
	if (process_handle == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	return TRUE;
}

auto UsermodeMemory::GetBaseAddress() -> DWORD_PTR
{
	TCHAR file_name[MAX_PATH] = {};
	TCHAR module_name[MAX_PATH];
	HMODULE * module_handle = nullptr;
	DWORD needed;
	DWORD modules;
	DWORD_PTR base_address = NULL;

	//
	// Set the hModules memory_size
	//
	EnumProcessModules(process_handle, module_handle, 0, &modules);
	module_handle = new HMODULE[modules / sizeof(HMODULE)];

	//
	// Get the Module name
	//
	GetModuleBaseName(process_handle, nullptr, file_name, sizeof(file_name));

	//
	// Get the base address
	//
	if (EnumProcessModules(process_handle, module_handle, sizeof(module_handle), &needed))
	{
		for (unsigned int i = 0; i < (needed / sizeof(HMODULE)); i++)
		{
			std::string std_file_name(file_name);

			if (GetModuleBaseName(process_handle, module_handle[i], module_name, sizeof module_name) && std_file_name == module_name)
			{
				base_address = reinterpret_cast<DWORD_PTR>(module_handle[i]);
				break;
			}
		}
	}

	delete[] module_handle;

	return base_address;
}
