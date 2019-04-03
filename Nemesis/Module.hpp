#pragma once

#include "ProcessMemory.hpp"
#include "Section.hpp"

#include <vector>
#include <Windows.h>

class Module
{
	ProcessMemory *process_memory;
	DWORD_PTR base_address;

public:
	const DWORD kFileAlignmentConstant = 0x200;

	BYTE *dos_stub;
	DWORD dos_stub_size;
	
	PIMAGE_DOS_HEADER dos_header;
	PIMAGE_NT_HEADERS32 nt_header32;
	PIMAGE_NT_HEADERS64 nt_header64;

	std::vector<Section> sections;

private:
	//
	// Init Functions
	//
	auto ReadHeader() -> BOOL;
	auto SetHeader(PVOID header_memory, DWORD header_size) -> VOID;
	auto SetSections() -> VOID;
	auto SetSectionSize(Section& section, DWORD_PTR section_pointer) const -> VOID;
	auto ReadSection(Section& section, DWORD_PTR section_pointer) const -> BOOL;

public:
	explicit Module(ProcessMemory* process_memory);
	Module(ProcessMemory *process_memory, DWORD_PTR base_address);
	~Module();

	//
	// Functions
	//
	auto Initialize() -> BOOL;

	auto SetFileAlignment() const -> VOID;
	auto SetEntryPoint(DWORD_PTR entry_point) const -> VOID;
	auto AlignSectionHeaders() -> VOID;
	auto FixHeader() -> VOID;
	auto RemoveIat() -> VOID;

	static auto GetInstructionByteCount(const BYTE* data, DWORD size) -> DWORD;
	static auto AlignValue(DWORD bad_value, DWORD align_to) -> DWORD;

	//
	// Checks
	//
	auto IsValidPeFile() const -> BOOL;
	auto Is64Bit() const -> BOOL;
	auto Is32Bit() const -> BOOL;

	//
	// Getters
	//
	auto GetImageSize() -> DWORD;
	auto GetSectionCount() const -> WORD;
	static auto GetHeaderSize()->DWORD;
};

