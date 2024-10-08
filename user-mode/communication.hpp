#pragma once

#include <Windows.h>

// Defines an IOCTL code for requesting the address of the executable.
#define IO_GET_EXECUTABLE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1337, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1338, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1339, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define IO_REQUEST_PROCESSID CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1340, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _KERNEL_READ_REQUEST
{
	ULONG processID;
	ULONG address;
	PVOID pBuffer;
	ULONG size;

} KERNEL_READ_REQUEST, * PKERNEL_READ_REQUEST;

typedef struct _KERNEL_WRITE_REQUEST
{
	ULONG processID;
	ULONG address;
	PVOID pBuffer;
	ULONG size;

} KERNEL_WRITE_REQUEST, * PKERNEL_WRITE_REQUEST;