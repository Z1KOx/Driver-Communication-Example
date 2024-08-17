#pragma once

#include "communication.hpp"

class KernelInterface
{
public:
	HANDLE hDriver;

	// Constructor: Opens a handle to the driver for communication.
	KernelInterface(LPCSTR registryPath) {
		hDriver = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, nullptr);
	}

	// Retrieves the executable address from the driver using an IOCTL request.
	DWORD getExecutableAddress()
	{
		if (hDriver == INVALID_HANDLE_VALUE) {
			return 0;
		}

		ULONG address;
		DWORD bytes;

		// Send an IOCTL request to the driver to get the executable address.
		if (DeviceIoControl(hDriver, IO_GET_EXECUTABLE_ADDRESS, &address, sizeof(address), &address, sizeof(address), &bytes, NULL)) {
			return address;
		}

		return 0;
	}
};