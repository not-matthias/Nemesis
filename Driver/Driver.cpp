#include <ntddk.h>
#include "ntos.h"

#pragma alloc_text( INIT, DriverEntry)
#pragma alloc_text( PAGE, IoctlDevice)

//
// IOCTLs
//
#define IOCTL_READ_REQUEST				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2222, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_BASE_ADDRESS_REQUEST		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2223, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

//
// Structures
//
typedef struct _READ_REQUEST
{
	//
	// In
	//
	ULONG Pid;
	DWORD_PTR TargetAddress;

	//
	// Both
	//
	SIZE_T BufferSize;

	// 
	// Out
	// 
	PVOID BufferAddress;
} READ_REQUEST, *PREAD_REQUEST;

typedef struct _BASE_ADDRESS_REQUEST
{
	//
	// In
	//
	ULONG Pid;

	// 
	// Out
	// 
	PVOID BaseAddress;
} BASE_ADDRESS_REQUEST, *PBASE_ADDRESS_REQUEST;

//
// Helper function
//
NTSTATUS CopyVirtualMemory(PVOID pSrc, PVOID pDest, SIZE_T Size)
{
	PEPROCESS Process;
	PSIZE_T pBytesCopied;

	__try
	{
		if (NT_SUCCESS(MmCopyVirtualMemory(Process, pSrc, PsGetCurrentProcess(), pDest, Size, UserMode, pBytesCopied)))
		{
			return STATUS_SUCCESS;
		}
		else
		{
			return STATUS_UNSUCCESSFUL;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return STATUS_UNSUCCESSFUL;
	}

	return STATUS_UNSUCCESSFUL;
}


//
// Device Handler
//
NTSTATUS DeviceControl(
	IN PDEVICE_OBJECT pDeviceObject,
	IN PIRP pIrp
)
{
	//
	// Return values
	//
	NTSTATUS Status = STATUS_SUCCESS;
	ULONG Bytes = 0;

	//
	// Request stuff
	//
	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(pIrp);
	ULONG ControlCode = pStack->Parameters.DeviceIoControl.IoControlCode;

	//
	// Handle the requests
	//
	switch (ControlCode)
	{
		//
		// IOCTL_READ_REQUEST
		//
	case IOCTL_READ_REQUEST:
		PREAD_REQUEST pReadRequest = (PREAD_REQUEST)pIrp->AssociatedIrp.SystemBuffer;



		break;

		//
		// IOCTL_BASE_ADDRESS_REQUEST
		//
	case IOCTL_BASE_ADDRESS_REQUEST:
		PBASE_ADDRESS_REQUEST pBaseAddressRequest = (PBASE_ADDRESS_REQUEST)pIrp->AssociatedIrp.SystemBuffer;

		if (pBaseAddressRequest != NULL)
		{
			PEPROCESS pProcess;

			//
			// Get the process
			//
			Status = PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(pBaseAddressRequest->Pid), &pProcess);

			// 
			// Check if found
			// 
			if (!NT_SUCCESS(Status))
			{
				pBaseAddressRequest->BaseAddress = 0;
				Status = STATUS_UNSUCCESSFUL;
				goto EXIT;
			}

			// 
			// Get the base address
			// 
			PVOID BaseAddress = PsGetProcessSectionBaseAddress(pProcess);

			//
			// Cleanup
			//
			ObDereferenceObject(pProcess);

			//
			// Return data
			//
			pBaseAddressRequest->BaseAddress = BaseAddress;
		}

		break;

	default:
		Status = STATUS_INVALID_PARAMETER;
		Bytes = 0;
	}

EXIT:
	pIrp->IoStatus.Status = Status;
	pIrp->IoStatus.Information = Bytes;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return Status;
}



//
// Entry Point
//
NTSTATUS DriverEntry(
	IN PDRIVER_OBJECT  pDriverObject,
	IN PUNICODE_STRING pRegistryPath
)
{
	UNREFERENCED_PARAMETER(pDriverObject);
	UNREFERENCED_PARAMETER(pRegistryPath);

	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceControl;

	return STATUS_SUCCESS;
}