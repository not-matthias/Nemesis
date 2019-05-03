#pragma once
#include <ntddk.h>

typedef struct _KAPC_STATE
{
	LIST_ENTRY ApcListHead[MaximumMode];
	struct _KPROCESS * Process;
	BOOLEAN KernelApcInProgress;
	BOOLEAN KernelApcPending;
	BOOLEAN UserApcPending;
} KAPC_STATE, *PKAPC_STATE, *PRKAPC_STATE;


NTKERNELAPI VOID KeStackAttachProcess(
	PRKPROCESS   PROCESS,
	PRKAPC_STATE ApcState
);

NTKERNELAPI VOID KeUnstackDetachProcess(
	IN PRKAPC_STATE ApcState
);

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(
	IN PEPROCESS Process
);

NTKERNELAPI NTSTATUS PsLookupProcessByProcessId(
	IN HANDLE ProcessId,
	OUT PEPROCESS * Process
);

NTKERNELAPI NTSTATUS NTAPI MmCopyVirtualMemory(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);
