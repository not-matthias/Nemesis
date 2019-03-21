#pragma once

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(
	IN PEPROCESS Process
);

NTKERNELAPI NTSTATUS PsLookupProcessByProcessId(
	IN HANDLE ProcessId, 
	OUT PEPROCESS *Process
);

NTKERNELAPI NTSTATUS NTAPI MmCopyVirtualMemory(
	IN PEPROCESS FromProcess, 
	IN PVOID FromAddress, 
	IN PEPROCESS ToProcess, 
	OUT PVOID ToAddress, 
	IN SIZE_T BufferSize, 
	IN KPROCESSOR_MODE PreviousMode, 
	OUT PSIZE_T NumberOfBytesCopied
);
