#pragma once

#include "communication.hpp"

class KernelInterface
{
public:
	KernelInterface(LPCSTR registryPath) {
		m_hDriver = CreateFileA(registryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, nullptr);
	}

	~KernelInterface() {
		CloseHandle(m_hDriver);
	}

	// Retrieves the executable address from the driver using an IOCTL request.
	DWORD getExecutableAddress()
	{
		if (m_hDriver == INVALID_HANDLE_VALUE) {
			return 0;
		}

		ULONG address;
		DWORD bytes;

		// Send an IOCTL request to the driver to get the executable address.
		if (DeviceIoControl(m_hDriver, IO_GET_EXECUTABLE_ADDRESS, &address, sizeof(address), &address, sizeof(address), &bytes, NULL)) {
			return address;
		}

		return 0;
	}

	DWORD getProcessID()
	{
		if (m_hDriver == INVALID_HANDLE_VALUE) {
			return 0;
		}

		ULONG processID;
		DWORD bytes;

		// Send an IOCTL request to the driver to get the executable address.
		if (DeviceIoControl(m_hDriver, IO_REQUEST_PROCESSID, &processID, sizeof(processID), &processID, sizeof(processID), &bytes, NULL)) {
			return processID;
		}

		return 0;
	}

	template<typename t>
	t ReadVirtualMemory(ULONG processID, ULONG readAddress, SIZE_T size)
	{
		t buffer;

		KERNEL_READ_REQUEST readRequest;

		readRequest.processID = processID;
		readRequest.address = readAddress;
		readRequest.pBuffer = &buffer;
		readRequest.size = size;

		if (DeviceIoControl(m_hDriver, IO_READ_REQUEST, &readRequest, sizeof(readRequest), &readRequest, sizeof(readRequest), 0, NULL)) {
			return buffer;
		}

		return buffer;
	}

	template<typename t>
	bool writeVirtualMemory(ULONG processID, ULONG writeAddress, t writeValue, SIZE_T size)
	{
		if (m_hDriver == INVALID_HANDLE_VALUE) {
			return false;
		}

		DWORD bytes;

		KERNEL_WRITE_REQUEST writeRequest;

		writeRequest.processID = processID;
		writeRequest.address = writeAddress;
		writeRequest.pBuffer = &writeValue;
		writeRequest.size = size;

		if (DeviceIoControl(m_hDriver, IO_WRITE_REQUEST, &writeRequest, sizeof(writeRequest), 0, 0, &bytes, NULL)) {
			return true;
		}

		return false;
	}

private:
	HANDLE m_hDriver{ nullptr };
};