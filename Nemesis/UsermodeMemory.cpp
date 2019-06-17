#include "stdafx.h"

#include "Logger.hpp"
#include "UsermodeMemory.hpp"

UsermodeMemory::UsermodeMemory(const DWORD process_id) : IMemorySource(process_id)
{
	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

	if (!process_handle.IsValid())
	{
		Logger::Log("Failed to open process.");
	}
}


auto UsermodeMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) -> std::shared_ptr<BYTE>
{
	if (!process_handle.IsValid())
	{
		return nullptr;
	}

	const auto buffer = std::shared_ptr<BYTE>(new BYTE[size], [](const BYTE * memory) { delete[] memory; });
	SIZE_T bytes_read;
	DWORD old_protect;

	// 
	// ReadProcessMemory
	// 
	if (!ReadProcessMemory(process_handle.Get(), reinterpret_cast<LPCVOID>(start_address), buffer.get(), size, &bytes_read))
	{
		Logger::Log("Failed to read process memory.");

		//
		// RPM Failed - Disable page protection
		//
		if (!VirtualProtectEx(process_handle.Get(), reinterpret_cast<LPVOID>(start_address), size, PAGE_READWRITE, &old_protect))
		{
			Logger::Log("Failed to change page protection.");
			return nullptr;
		}

		// 
		// ReadProcessMemory
		// 
		if (!ReadProcessMemory(process_handle.Get(), reinterpret_cast<LPCVOID>(start_address), buffer.get(), size, &bytes_read))
		{
			Logger::Log("Failed to read process memory.");
		}

		VirtualProtectEx(process_handle.Get(), reinterpret_cast<LPVOID>(start_address), size, old_protect, &old_protect);
	}

	return buffer;
}

auto UsermodeMemory::IsValid() -> BOOL
{
	return process_handle.IsValid();
}

auto UsermodeMemory::GetBaseAddress() -> DWORD_PTR
{
	WCHAR file_name[MAX_PATH] = {0};
	WCHAR module_name[MAX_PATH] = {0};
	HMODULE * module_handle = nullptr;
	DWORD needed, modules;
	DWORD_PTR base_address = NULL;

	//
	// Set the hModules memory_size
	//
	EnumProcessModules(process_handle.Get(), module_handle, 0, &modules);
	module_handle = new HMODULE[modules / sizeof(HMODULE)];

	//
	// Get the Module name
	//
	GetModuleBaseName(process_handle.Get(), nullptr, file_name, sizeof(file_name));

	//
	// Get the base address
	//
	if (EnumProcessModules(process_handle.Get(), module_handle, sizeof(module_handle), &needed))
	{
		for (unsigned int i = 0; i < (needed / sizeof(HMODULE)); i++)
		{
			std::wstring std_file_name(file_name);

			if (GetModuleBaseName(process_handle.Get(), module_handle[i], module_name, sizeof module_name) && std_file_name == module_name)
			{
				base_address = reinterpret_cast<DWORD_PTR>(module_handle[i]);
				break;
			}
		}
	}

	delete[] module_handle;

	return base_address;
}
