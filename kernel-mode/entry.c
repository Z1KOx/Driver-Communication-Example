#pragma warning (disable: 4047 4024)

#include "entry.h"
#include "data.h"
#include "events.h"
#include "communication.h"

NTSTATUS DriverEntry( PDRIVER_OBJECT pDriverObject,
	                  PUNICODE_STRING pRegistryPath )
{
	UNREFERENCED_PARAMETER( pRegistryPath );

	// Set the function to be called when the driver is unloaded for cleanup tasks.
	pDriverObject->DriverUnload = UnloadDriver;

	DbgPrintEx( 0, 0, "Load Driver" );

	//	This function registers the `ImageLoadCallback` function.
	//	ImageLoadCallBack gets called by the system whenever any dll or executable is loaded into a process.
	//	In this callback, we check if a specific executable is loaded and take action if it is.
	PsSetLoadImageNotifyRoutine( ImageLoadCallback );

	//	Initializes the `dev` variable with the Unicode string representing the device name `\\Device\\Z1KODriver`.
	RtlInitUnicodeString( &dev, L"\\Device\\Z1KODriver" );

	//	Initializes the `dos` variable with the Unicode string representing the symbolic link name `\\DosDevices\\Z1KODriver`.
	//	This symbolic link allows user-mode applications to access the device using this name.
	RtlInitUnicodeString( &dos, L"\\DosDevices\\Z1KODriver" );

	//	Creates a new device object for the driver.
	//	More infos of the parameters you can find here: https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-iocreatedevice
	IoCreateDevice( pDriverObject,
		            0,
		            &dev,
		            FILE_DEVICE_UNKNOWN,
		            FILE_DEVICE_SECURE_OPEN,
		            FALSE,
		            &pDeviceObject );

	//	Creates a symbolic link between the user-mode path (`\\DosDevices\\Z1KODriver`)
	//	and the kernel-mode device path (`\\Device\\Z1KODriver`).
	//	This allows user-mode applications to access the device using the user-mode path.
	IoCreateSymbolicLink( &dos, &dev );

	//	Set the driver's major function pointers for handling different types of I/O requests.
	//	- `IRP_MJ_CREATE`: Function to handle requests to open or create a handle to the device.
	//	- `IRP_MJ_CLOSE`: Function to handle requests to close the handle to the device.
	//	- `IRP_MJ_DEVICE_CONTROL`: Function to handle control requests sent to the device.
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = createCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = closeCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ioControl;

	//	Configure the device object to use direct I/O, meaning no additional buffering by the system.
	pDeviceObject->Flags |= DO_DIRECT_IO;
	//	Indicate that the device is fully initialized and ready to handle I/O requests.
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS UnloadDriver( PDRIVER_OBJECT pDriverObject )
{
	UNREFERENCED_PARAMETER( pDriverObject );

	DbgPrintEx( 0, 0, "Unload Driver" );

	//	This stops the system from calling the ImageLoadCallback function when modules (executables or DLLs) are loaded.
	PsRemoveLoadImageNotifyRoutine( ImageLoadCallback );

	//	This removes the user-mode path used to access the device object, so no further requests can be sent to it.
	IoDeleteSymbolicLink( &dos );

	//	This removes the device object created for the driver and frees all associated resources.
	IoDeleteDevice( pDriverObject->DeviceObject );

	return STATUS_SUCCESS;
}