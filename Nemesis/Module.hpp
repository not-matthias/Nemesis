#pragma once

#include "ProcessMemory.hpp"
#include "Section.hpp"

#include <vector>
#include <Windows.h>

class Module
{

	/**
	 * \brief The process memory wrapper
	 */
	ProcessMemory *process_memory;

	/**
	 * \brief The base address of the module
	 */
	DWORD_PTR base_address;

public:
	/**
	 * \brief The default file alignment constant
	 */
	const DWORD file_alignment_constant = 0x200;

	/**
	 * \brief The dos stub memory
	 */
	BYTE *dos_stub;

	/**
	 * \brief The dos stub size
	 */
	DWORD dos_stub_size;


	/**
	 * \brief The dos header of a module
	 */
	PIMAGE_DOS_HEADER dos_header;

	/**
	 * \brief The 32 bit nt header of a module.
	 */
	PIMAGE_NT_HEADERS32 nt_header32;

	/**
	 * \brief The 64 bit nt header of a module
	 */
	PIMAGE_NT_HEADERS64 nt_header64;

	/**
	 * \brief Contains the sections of a module
	 */
	std::vector<Section> sections;

private:

	//
	//
	// Init Functions
	//
	//

	/**
	 * \brief Reads the header from the memory
	 * \return true if successful
	 */
	auto ReadHeader() -> BOOL;

	/**
	 * \brief Sets the headers
	 * \param header_memory the header memory
	 * \param header_size the header memory size
	 */
	auto SetHeader(BYTE* header_memory, DWORD header_size) -> VOID;

	/**
	 * \brief Sets the sections
	 */
	auto SetSections() -> VOID;

	/**
	 * \brief Sets the section size
	 * \param section the specified section
	 * \param section_pointer the section poitner
	 */
	auto SetSectionSize(Section& section, DWORD_PTR section_pointer) const -> VOID;

	/**
	 * \brief Reads the section from memory
	 * \param section the section object
	 * \param section_pointer the section pointer
	 * \return true if successful
	 */
	auto ReadSection(Section& section, DWORD_PTR section_pointer) const -> BOOL;

public:

	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Stores the parameters.
	 * \param process_memory used for reading the memory
	 */
	explicit Module(ProcessMemory* process_memory);

	/**
	 * \brief Stores the parameters.
	 * \param process_memory the memory wrapper of the module
	 * \param base_address the base address of the module
	 */
	Module(ProcessMemory *process_memory, DWORD_PTR base_address);

	/**
	 * \brief Deletes the section buffers
	 */
	~Module();


	//
	//
	// Other functions
	//
	//

	/**
	 * \brief Initializes the module
	 * \return true if successful
	 */
	auto Initialize() -> BOOL;

	/**
	 * \brief Sets the file alignment in the header
	 */
	auto SetFileAlignment() const -> VOID;

	/**
	 * \brief Sets the entry point in the header
	 * \param entry_point the address of the entry point
	 */
	auto SetEntryPoint(DWORD_PTR entry_point) const -> VOID;

	/**
	 * \brief Aligns the section headers
	 */
	auto AlignSectionHeaders() -> VOID;

	/**
	 * \brief Fixes the header by removing iat and setting the sizes
	 */
	auto FixHeader() -> VOID;

	/**
	 * \brief Removes the iat
	 */
	auto RemoveIat() -> VOID;


	//
	//
	// Helper functions
	//
	//

	/**
	 * \brief Finds the instruction count in the data
	 * \param data the memory buffer
	 * \param size the size of the buffer
	 * \return the instruction count
	 */
	static auto GetInstructionByteCount(const BYTE* data, DWORD size) -> DWORD;

	/**
	 * \brief Aligns the value
	 * \param bad_value the bad value
	 * \param align_to the alignment value
	 * \return the new value
	 */
	static auto AlignValue(DWORD bad_value, DWORD align_to) -> DWORD;


	//
	//
	// Checks
	//
	//

	/**
	 * \brief Checks whether the module is valid
	 * \return true if it's valid
	 */
	auto IsValidModule() const -> BOOL;

	/**
	 * \brief Checks whether the module is 64 bit
	 * \return true if it's 64 bit
	 */
	auto Is64Bit() const -> BOOL;

	/**
	 * \brief Checks whether the module is 32 bit
	 * \return true if it's 32 bit
	 */
	auto Is32Bit() const -> BOOL;


	//
	//
	// Getters
	//
	//

	/**
	 * \brief Returns the image size
	 * \return the image size
	 */
	auto GetImageSize() -> DWORD;

	/**
	 * \brief Returns the number of sections
	 * \return the section count
	 */
	auto GetSectionCount() const -> WORD;

	/**
	 * \brief Returns the header size
	 * \return the header size
	 */
	static auto GetHeaderSize()->DWORD;
};

