#pragma warning (disable : 4047)

#include "events.h"
#include "data.h"

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback( PUNICODE_STRING fullImageName,
	                                          HANDLE processID,
	                                          PIMAGE_INFO imageInfo )
{
	//	Check if the loaded image name matches the specific path we're interested in.
	if (wcsstr(fullImageName->Buffer, L"\\AssaultCubev12\\bin_win32\\ac_client.exe"))
	{
		DbgPrintEx( 0, 0, "ac_client.exe found" );

		//	Store the base address of the loaded image into the `AssaultCubeClientAddress` variable.
		AssaultCubeClientAddress = imageInfo->ImageBase;

		DbgPrintEx( 0, 0, "ProcessID: %d", processID );
	}

	return STATUS_SUCCESS;
}