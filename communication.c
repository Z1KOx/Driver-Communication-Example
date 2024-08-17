#include "communication.h"
#include "data.h"

//	Handles IOCTL requests for the device.
NTSTATUS ioControl(PDEVICE_OBJECT deviceObject,
	PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObject);

	//	Initialize status as unsuccessful; will be set to successful if the operation is completed correctly.
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	ULONG byteIO = 0;

	//  Retrieves the current stack location for the IRP, which contains the parameters for the I/O request from the user-mode program.
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

	//	Retrieves the IOCTL code from the current stack location, which specifies the type of control operation requested by the user-mode program.
	ULONG controlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	//	If the user-mode program requested the executable address (which has the identifier 0x1337) handle the request.
	if (controlCode == IO_GET_EXECUTABLE_ADDRESS)
	{
		//	Access the user-mode program buffer
		PULONG output = (PULONG)irp->AssociatedIrp.SystemBuffer;
		//	Write the address of the executable `AssaultCubeClientAddress` into the user-mode buffer.
		*output = AssaultCubeClientAddress;

		DbgPrintEx(0, 0, "[user-mode] executable Assaultcube address requested");

		//	Set status to success.
		status = STATUS_SUCCESS;
		//	Set the number of bytes transferred to the size of the output buffer.
		byteIO = sizeof(*output);
	}
	else {
		byteIO = 0;
	}

	//	Set the IRP status to indicate success or failure of the operation.
	irp->IoStatus.Status = status;
	//	Set the number of bytes transferred during the I/O operation.
	irp->IoStatus.Information = byteIO;

	//	Complete the I/O request, marking it as finished.
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}

//	Handles a CLOSE request for the device.
NTSTATUS closeCall(PDEVICE_OBJECT deviceObject,
	PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObject);

	//	Set status to success.
	irp->IoStatus.Status = STATUS_SUCCESS;
	//	Set our I/O information to 0.
	irp->IoStatus.Information = 0;

	//	Complete the I/O request, marking it as finished.
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	DbgPrintEx(0, 0, "CLOSE I/O Requests");

	return STATUS_SUCCESS;
}

//	Handles a CREATE request for the device.
NTSTATUS createCall(PDEVICE_OBJECT deviceObject,
	PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObject);

	//	Set status to success.
	irp->IoStatus.Status = STATUS_SUCCESS;
	//	Set our I/O information to 0.
	irp->IoStatus.Information = 0;

	//	Complete the I/O request, marking it as finished.
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	DbgPrintEx(0, 0, "CREATE I/O Requests");

	return STATUS_SUCCESS;
}