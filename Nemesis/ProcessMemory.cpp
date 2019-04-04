#include "ProcessMemory.hpp"

#include <unordered_map>
#include <ostream>
#include <iostream>

#include "UsermodeMemory.hpp"
#include "KernelMemory.hpp"

char * ProcessMemory::current_memory_source = nullptr;

ProcessMemory::ProcessMemory(const DWORD process_id)
{
	this->process_id = process_id;

	//
	// Add the memory sources
	//
	this->memory_sources.insert(std::make_pair("user_mode", new UsermodeMemory(process_id)));
	this->memory_sources.insert(std::make_pair("kernel_mode", new KernelMemory(process_id)));


	//
	// Find the memory source
	//
	IMemorySource * memory_source = memory_sources[current_memory_source];


	//
	// Set the usermode memory source
	//
	if (memory_source != nullptr)
	{
		this->memory_source = memory_source;
	}
	else
	{
		this->memory_source = memory_sources.at(0);
	}
}

ProcessMemory::~ProcessMemory()
{
	delete memory_source;
}

auto ProcessMemory::ReadMemory(const DWORD_PTR start_address, const SIZE_T size) const -> PVOID
{
	return this->memory_source->ReadMemory(start_address, size);
}

auto ProcessMemory::IsValid() const -> BOOL
{
	return memory_source != nullptr && memory_source->IsValid();
}

auto ProcessMemory::GetBaseAddress() const -> DWORD_PTR
{
	return memory_source->GetBaseAddress();
}

auto ProcessMemory::GetMemorySources() -> std::vector<const char *>
{
	std::vector<const char *> temp;

	//
	// Fill the list
	//
	// TODO: Find a better way
	temp.emplace_back("user_mode");
	temp.emplace_back("kernel_mode");

	return temp;
}

auto ProcessMemory::SetMemorySource(char * memory_source_name) -> VOID
{
	current_memory_source = memory_source_name;
}
