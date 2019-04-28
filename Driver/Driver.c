#include <ntddk.h>
#include "ntos.h"
#include "Logger.h"

#define DEBUG

//
// IOCTLs
//
#define IOCTL_READ_REQUEST				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2222, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IOCTL_BASE_ADDRESS_REQUEST		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2223, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


//
// Structures
//

/**
 * \brief The struct for the kernel read request.
 */
typedef struct _READ_REQUEST
{
	//
	// In
	//
	ULONG process_id;
	DWORD_PTR target_address;

	//
	// Both
	//
	SIZE_T buffer_size;

	// 
	// Out
	// 
	PVOID buffer_address;
} READ_REQUEST, *PREAD_REQUEST;

/**
 * \brief The struct for the base address request.
 */
typedef struct _BASE_ADDRESS_REQUEST
{
	//
	// In
	//
	ULONG process_id;

	// 
	// Out
	// 
	PVOID base_address;
} BASE_ADDRESS_REQUEST, *PBASE_ADDRESS_REQUEST;


//
// Variables
//
PDEVICE_OBJECT g_device_object;
UNICODE_STRING device_name, symbolic_link_name;


//
// Helper function
//
NTSTATUS CopyVirtualMemory(const HANDLE process_id, const PVOID source_address, const PVOID destination_address, const SIZE_T size)
{
	PEPROCESS process = NULL;
	PSIZE_T bytes_copied = NULL;

	Log("Reading virtual memory.");

	__try
	{
		//
		// Open the process
		//
		if (NT_SUCCESS(PsLookupProcessByProcessId(process_id, &process)))
		{
			//
			// Read virtual memory
			//
			if (NT_SUCCESS(MmCopyVirtualMemory(process, source_address, PsGetCurrentProcess(), destination_address, size, KernelMode, bytes_copied)))
			{
				Log("Successfully read virtual memory.");

				ObDereferenceObject(process);
				return STATUS_SUCCESS;
			}
			else
			{
				Log("Failed to read virtual memory.");

				ObDereferenceObject(process);
				return STATUS_UNSUCCESSFUL;
			}
		}
		else
		{
			Log("Failed to lookup process.");

			return STATUS_UNSUCCESSFUL;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		Log("Something went wrong while reading virtual memory.");

		return STATUS_UNSUCCESSFUL;
	}
}


//
// Device Handler
//
NTSTATUS DeviceControl(PDEVICE_OBJECT device_object, const PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	//
	// Return values
	//
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG bytes = 0;

	//
	// Request stuff
	//
	const PIO_STACK_LOCATION stack_location = IoGetCurrentIrpStackLocation(irp);
	const ULONG control_code = stack_location->Parameters.DeviceIoControl.IoControlCode;

	PREAD_REQUEST read_request;
	PBASE_ADDRESS_REQUEST base_address_request;


	//
	// Handle the requests
	//
	switch (control_code)
	{
	case IOCTL_READ_REQUEST:
		read_request = (PREAD_REQUEST)irp->AssociatedIrp.SystemBuffer;

		//
		// Check request data
		//
		if (read_request != NULL && read_request->target_address < 0x7FFFFFFFFFFF)
		{
			//
			// Read virtual memory
			//
			status = CopyVirtualMemory((HANDLE)read_request->process_id, (PVOID)&read_request->target_address, (PVOID)read_request->buffer_address,
			                           read_request->buffer_size);
			bytes = sizeof(READ_REQUEST);
		}
		break;


	case IOCTL_BASE_ADDRESS_REQUEST:
		base_address_request = (PBASE_ADDRESS_REQUEST)irp->AssociatedIrp.SystemBuffer;

		//
		// Check request data
		//
		if (base_address_request != NULL)
		{
			PEPROCESS pProcess;

			//
			// Get the process
			//
			status = PsLookupProcessByProcessId((HANDLE)base_address_request->process_id, &pProcess);

			// 
			// Check if found (and return)
			// 
			if (!NT_SUCCESS(status))
			{
				base_address_request->base_address = 0;

				break;
			}

			// 
			// Get the base address
			// 
			const PVOID base_address = PsGetProcessSectionBaseAddress(pProcess);

			//
			// Cleanup
			//
			ObDereferenceObject(pProcess);

			//
			// Return data
			//
			base_address_request->base_address = base_address;
			status = STATUS_SUCCESS;
			bytes = sizeof(BASE_ADDRESS_REQUEST);
		}
		break;


	default:
		status = STATUS_INVALID_PARAMETER;
		bytes = 0;
	}

	irp->IoStatus.Status = status;
	irp->IoStatus.Information = bytes;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}


//
// Unload the driver
//
VOID DriverUnload(const PDRIVER_OBJECT driver_object)
{
	//
	// Delete the symbolic link
	//
	IoDeleteSymbolicLink(&symbolic_link_name);

	//
	// Delete the device object
	//
	IoDeleteDevice(driver_object->DeviceObject);

	Log("Driver unloaded.\n");
}


NTSTATUS UnsupportedDispatch(PDEVICE_OBJECT device_object, const PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

NTSTATUS CreateDispatch(PDEVICE_OBJECT device_object, const PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

NTSTATUS CloseDispatch(PDEVICE_OBJECT device_object, const PIRP irp)
{
	UNREFERENCED_PARAMETER(device_object);

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

//
// Entry Point
//
NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(registry_path);

	//
	// Initialize the variables
	//
	RtlInitUnicodeString(&device_name, L"\\Device\\KernelMemory");
	RtlInitUnicodeString(&symbolic_link_name, L"\\DosDevices\\KernelMemory");

	//
	// Create the device object
	//
	if (!NT_SUCCESS(IoCreateDevice(driver_object, 0, &device_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &g_device_object)))
	{
		Log("Failed to create device object.\n");
		return STATUS_UNSUCCESSFUL;
	}

	//
	// Create symbolic link
	//
	if (!NT_SUCCESS(IoCreateSymbolicLink(&symbolic_link_name, &device_name)))
	{
		Log("Failed to create symbolic link.\n");
		IoDeleteDevice(g_device_object);

		return STATUS_UNSUCCESSFUL;
	}

	//
	// Set major functions
	//
	for (ULONG i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		driver_object->MajorFunction[i] = &UnsupportedDispatch;

	driver_object->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DeviceControl;
	driver_object->MajorFunction[IRP_MJ_CREATE] = &CreateDispatch;
	driver_object->MajorFunction[IRP_MJ_CLOSE] = &CloseDispatch;
	driver_object->DriverUnload = DriverUnload;

	//
	// Set flags
	//
	driver_object->Flags |= DO_BUFFERED_IO;
	driver_object->Flags &= ~DO_DEVICE_INITIALIZING;

	Log("Driver loaded.\n");

	return STATUS_SUCCESS;
}
