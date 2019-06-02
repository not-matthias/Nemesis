#pragma once

#include <string>
#include <vector>

#include "ProcessExport.hpp"

namespace structs
{
	typedef struct _UNICODE_STRING
	{
		USHORT Length;
		USHORT MaximumLength;
		PWSTR Buffer;
	} UNICODE_STRING, *PUNICODE_STRING;

	typedef struct _LDR_DATA_TABLE_ENTRY
	{
		LIST_ENTRY InLoadOrderLinks;
		LIST_ENTRY InMemoryOrderLinks;
		LIST_ENTRY InInitializationOrderLinks;
		PVOID DllBase;
		PVOID EntryPoint;
		ULONG SizeOfImage;
		UNICODE_STRING FullDllName;
		UNICODE_STRING BaseDllName;
		ULONG Flags;
		WORD LoadCount;
		WORD TlsIndex;

		union
		{
			LIST_ENTRY HashLinks;

			struct
			{
				PVOID SectionPointer;
				ULONG CheckSum;
			};
		};

		union
		{
			ULONG TimeDateStamp;
			PVOID LoadedImports;
		};

		_ACTIVATION_CONTEXT * EntryPointActivationContext;
		PVOID PatchInformation;
		LIST_ENTRY ForwarderLinks;
		LIST_ENTRY ServiceTagLinks;
		LIST_ENTRY StaticLinks;
	} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

	typedef struct _PEB_LDR_DATA
	{
		ULONG Length;
		BOOLEAN Initialized;
		PVOID SsHandle;
		LIST_ENTRY InLoadOrderModuleList;
		LIST_ENTRY InMemoryOrderModuleList;
		LIST_ENTRY InInitializationOrderModuleList;
	} PEB_LDR_DATA, *PPEB_LDR_DATA;

	typedef struct _PEB
	{
		union
		{
			struct
			{
				BYTE InheritedAddressSpace;
				BYTE ReadImageFileExecOptions;
				BYTE BeingDebugged;
				BYTE BitField;
			};

			DWORD64 dummy01;
		};

		DWORD64 Mutant;
		DWORD64 ImageBaseAddress;
		PPEB_LDR_DATA Ldr;
		DWORD64 ProcessParameters;
		DWORD64 SubSystemData;
		DWORD64 ProcessHeap;
		DWORD64 FastPebLock;
		DWORD64 AtlThunkSListPtr;
		DWORD64 IFEOKey;
		DWORD64 CrossProcessFlags;
		DWORD64 UserSharedInfoPtr;
		DWORD SystemReserved;
		DWORD AtlThunkSListPtr32;
		DWORD64 ApiSetMap;
		DWORD64 TlsExpansionCounter;
		DWORD64 TlsBitmap;
		DWORD TlsBitmapBits[2];
		DWORD64 ReadOnlySharedMemoryBase;
		DWORD64 HotpatchInformation;
		DWORD64 ReadOnlyStaticServerData;
		DWORD64 AnsiCodePageData;
		DWORD64 OemCodePageData;
		DWORD64 UnicodeCaseTableData;
		DWORD NumberOfProcessors;

		union
		{
			DWORD NtGlobalFlag;
			DWORD dummy02;
		};

		LARGE_INTEGER CriticalSectionTimeout;
		DWORD64 HeapSegmentReserve;
		DWORD64 HeapSegmentCommit;
		DWORD64 HeapDeCommitTotalFreeThreshold;
		DWORD64 HeapDeCommitFreeBlockThreshold;
		DWORD NumberOfHeaps;
		DWORD MaximumNumberOfHeaps;
		DWORD64 ProcessHeaps;
		DWORD64 GdiSharedHandleTable;
		DWORD64 ProcessStarterHelper;
		DWORD64 GdiDCAttributeList;
		DWORD64 LoaderLock;
		DWORD OSMajorVersion;
		DWORD OSMinorVersion;
		WORD OSBuildNumber;
		WORD OSCSDVersion;
		DWORD OSPlatformId;
		DWORD ImageSubsystem;
		DWORD ImageSubsystemMajorVersion;
		DWORD64 ImageSubsystemMinorVersion;
		DWORD64 ActiveProcessAffinityMask;
		DWORD64 GdiHandleBuffer[30];
		DWORD64 PostProcessInitRoutine;
		DWORD64 TlsExpansionBitmap;
		DWORD TlsExpansionBitmapBits[32];
		DWORD64 SessionId;
		ULARGE_INTEGER AppCompatFlags;
		ULARGE_INTEGER AppCompatFlagsUser;
		DWORD64 pShimData;
		DWORD64 AppCompatInfo;
		UNICODE_STRING CSDVersion;
		DWORD64 ActivationContextData;
		DWORD64 ProcessAssemblyStorageMap;
		DWORD64 SystemDefaultActivationContextData;
		DWORD64 SystemAssemblyStorageMap;
		DWORD64 MinimumStackCommit;
		DWORD64 FlsCallback;
		LIST_ENTRY FlsListHead;
		DWORD64 FlsBitmap;
		DWORD FlsBitmapBits[4];
		DWORD64 FlsHighIndex;
		DWORD64 WerRegistrationData;
		DWORD64 WerShipAssertPtr;
		DWORD64 pContextData;
		DWORD64 pImageHeaderHash;
		DWORD64 TracingFlags;
	} PEB64, PPEB64;

	struct PROCESS_BASIC_INFORMATION
	{
		DWORD_PTR ExitStatus;
		PEB * PebBaseAddress;
		DWORD_PTR AffinityMask;
		DWORD_PTR BasePriority;
		ULONG_PTR UniqueProcessId;
		DWORD_PTR InheritedFromUniqueProcessId;
	};

	using PEB = PEB64;
	using PPEB = PPEB64;
	using LDR_DATA_TABLE_ENTRY = LDR_DATA_TABLE_ENTRY64;
	using PLDR_DATA_TABLE_ENTRY = PLDR_DATA_TABLE_ENTRY64;
}


class ProcessUtils
{
public:
	/**
	 * \brief Creates the process list struct.
	 * \return the structure
	 */
	static auto GetProcessList() -> std::vector<ProcessElement>;

	/**
	 * \brief Creates the module array.
	 * \param process_id the target process id
	 * \return the module array
	 */
	static auto GetModuleList(DWORD process_id) -> std::vector<ModuleElement>;

	/**
	 * \brief Creates the module array manually (should be use when you can't get a VM_READ process handle).
	 * \param process_id the target process id
	 * \return the module array
	 */
	static auto GetModuleListManually(DWORD process_id) -> std::vector<ModuleElement>;

	/**
	 * \brief Creates the memory regions array.
	 * \param process_id the target process id
	 * \return the memory array
	 */
	static auto GetMemoryList(DWORD process_id) -> std::vector<MemoryElement>;

	/**
	 * \brief Returns the path of the process' main module.
	 * \param process_id the target process id
	 * \return the path to the main module
	 */
	static auto GetFilePath(DWORD process_id) -> std::string;
};
