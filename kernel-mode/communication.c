#pragma warning (disable : 4022)

#include "communication.h"
#include "data.h"
#include "memory.h"

// Handles IOCTL requests for the device.
NTSTATUS ioControl( PDEVICE_OBJECT deviceObject,
	                PIRP irp )
{
	UNREFERENCED_PARAMETER( deviceObject );

	// Initialize status as unsuccessful; will be set to successful if the operation is completed correctly.
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG byteIO = 0;

	// Retrieves the current stack location for the IRP, which contains the parameters for the I/O request from the user-mode program.
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation( irp );

	// Retrieves the IOCTL code from the current stack location, which specifies the type of control operation requested by the user-mode program.
	ULONG controlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	// If the user-mode program requested the executable address.
	switch (controlCode)
	{
	case IO_GET_EXECUTABLE_ADDRESS:
	{
		// Access the user-mode program buffer
		PULONG output = (PULONG)irp->AssociatedIrp.SystemBuffer;

		// Write the address of the executable `AssaultCubeClientAddress` into the user-mode buffer.
		*output = AssaultCubeClientAddress;

		DbgPrintEx(0, 0, "[user-mode] Executable Assaultcube address requested");

		// Set status to success.
		status = STATUS_SUCCESS;
		// Set the number of bytes transferred to the size of the output buffer.
		byteIO = sizeof(*output);
		break;
	}
	case IO_REQUEST_PROCESSID:
	{
		// Access the user-mode program buffer
		PULONG output = (PULONG)irp->AssociatedIrp.SystemBuffer;

		// Write the address of the executable `AssaultCubeClientAddress` into the user-mode buffer.
		*output = processID;

		DbgPrintEx(0, 0, "[user-mode] ProcessID requested");

		status = STATUS_SUCCESS;
		byteIO = sizeof(*output);

		break;
	}
	case IO_READ_REQUEST:
	{
		// Retrieve the read request buffer from the user-mode application.
		PKERNEL_READ_REQUEST readInput = (PKERNEL_READ_REQUEST)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS process;

		// Validate the process ID by looking up the target process.
		if (NT_SUCCESS(PsLookupProcessByProcessId(readInput->processID, &process)))
		{
			// Copies data from the specified address in the target process's memory.
			KernelReadVirtualMemory(process, readInput->address, readInput->pBuffer, readInput->size);

			DbgPrintEx(0, 0, "[user-mode] Read requested");

			status = STATUS_SUCCESS;
			byteIO = sizeof(KERNEL_READ_REQUEST);
		}
		break;
	}
	case IO_WRITE_REQUEST:
	{
		// Retrieve the write request buffer from the user-mode application.
		PKERNEL_WRITE_REQUEST writeInput = (PKERNEL_WRITE_REQUEST)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS process;

		// Validate the process ID by looking up the target process.
		if (NT_SUCCESS(PsLookupProcessByProcessId(writeInput->processID, &process)))
		{
			// Perform the memory write operation: write data from the user-mode buffer to the target process's memory.
			KernelWriteVirtualMemory(process, writeInput->pBuffer, writeInput->address, writeInput->size);

			DbgPrintEx(0, 0, "[user-mode] Write requested");

			status = STATUS_SUCCESS;
			byteIO = sizeof(KERNEL_WRITE_REQUEST);
		}
		break;
	}
	default:
		byteIO = 0;
	}

	// Set the IRP status to indicate success or failure of the operation.
	irp->IoStatus.Status = status;
	// Set the number of bytes transferred during the I/O operation.
	irp->IoStatus.Information = byteIO;

	// Complete the I/O request, marking it as finished.
	IoCompleteRequest( irp, IO_NO_INCREMENT );

	return status;
}

// Handles a CLOSE request for the device.
NTSTATUS closeCall( PDEVICE_OBJECT deviceObject,
	                PIRP irp )
{
	UNREFERENCED_PARAMETER( deviceObject );

	// Set status to success.
	irp->IoStatus.Status = STATUS_SUCCESS;
	// Set our I/O information to 0.
	irp->IoStatus.Information = 0;

	//	Complete the I/O request, marking it as finished.
	IoCompleteRequest( irp, IO_NO_INCREMENT );

	DbgPrintEx( 0, 0, "CLOSE I/O Requests" );

	return STATUS_SUCCESS;
}

// Handles a CREATE request for the device.
NTSTATUS createCall( PDEVICE_OBJECT deviceObject,
	                 PIRP irp )
{
	UNREFERENCED_PARAMETER( deviceObject );

	// Set status to success.
	irp->IoStatus.Status = STATUS_SUCCESS;
	// Set our I/O information to 0.
	irp->IoStatus.Information = 0;

	// Complete the I/O request, marking it as finished.
	IoCompleteRequest( irp, IO_NO_INCREMENT );

	DbgPrintEx( 0, 0, "CREATE I/O Requests" );

	return STATUS_SUCCESS;
}