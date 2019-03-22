#pragma once

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(
	IN PEPROCESS Process
);

NTKERNELAPI NTSTATUS PsLookupProcessByProcessId(
	IN HANDLE ProcessId, 
	OUT PEPROCESS *Process
);

NTKERNELAPI NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);
