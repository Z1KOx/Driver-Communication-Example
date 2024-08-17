#pragma once

#include <ntifs.h>

// Defines an IOCTL code to request the executable address from the driver.
#define IO_GET_EXECUTABLE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1337, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

NTSTATUS ioControl(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS closeCall(PDEVICE_OBJECT deviceObject, PIRP irp);
NTSTATUS createCall(PDEVICE_OBJECT deviceObject, PIRP irp);