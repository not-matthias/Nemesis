#include "DumpExport.hpp"

#include "FileWriter.hpp"
#include "Module.hpp"

auto DumpProcessExport(const DWORD process_id, const LPCSTR file_name) -> BOOL
{
	//
	// Create the memory wrapper
	//
	ProcessMemory process_memory(process_id);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the module
	//
	Module module(&process_memory);
	if (!module.Initialize())
	{
		return FALSE;
	}

	module.SetFileAlignment();
	module.AlignSectionHeaders();
	module.FixHeader();
	module.RemoveIat();

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&module))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

auto DumpModuleExport(const DWORD process_id, const DWORD_PTR base_address, const LPCSTR file_name) -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory process_memory(process_id);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the pe file
	//
	Module module(&process_memory, base_address);
	if (!module.Initialize())
	{
		return FALSE;
	}

	module.SetFileAlignment();
	module.AlignSectionHeaders();
	module.FixHeader();
	module.RemoveIat();

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&module))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

auto DumpMemoryExport(const DWORD process_id, const DWORD_PTR start_address, const DWORD size, const LPCSTR file_name) -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory process_memory(process_id);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the Memory
	//
	MemoryElement memory(&process_memory, start_address, size);
	if (!memory.Initialize())
	{
		return FALSE;
	}

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&memory))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

auto DumpDriverExport(const DWORD_PTR base_address, const LPCSTR file_name) -> BOOL
{
	//
	// Create the Memory wrapper
	//
	ProcessMemory process_memory(4);
	if (!process_memory.IsValid())
	{
		return FALSE;
	}

	//
	// Create and initialize the pe file
	//
	Module module(&process_memory, base_address);
	if (!module.Initialize())
	{
		return FALSE;
	}

	module.SetFileAlignment();
	module.AlignSectionHeaders();
	module.FixHeader();
	module.RemoveIat();

	//
	// Write to file
	//
	FileWriter file_writer(file_name);
	if (file_writer.WriteToFile(&module))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
