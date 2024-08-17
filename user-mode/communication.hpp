#pragma once

#include <Windows.h>

// Defines an IOCTL code for requesting the address of the executable.
#define IO_GET_EXECUTABLE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1337, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)