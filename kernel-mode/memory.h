#pragma once

#pragma warning(disable: 4047 4024)

#include <ntifs.h>

NTSTATUS NTAPI MmCopyVirtualMemory(	PEPROCESS sourceProcess,
									PVOID sourceAddress,
									PEPROCESS targetProcess,
									PVOID targetAddress,
									SIZE_T bufferSize,
									KPROCESSOR_MODE previousMode,
									PSIZE_T returnSize );

NTSTATUS KernelReadVirtualMemory(PEPROCESS process, PVOID sourceAddress, PVOID targetAddress, SIZE_T size);
NTSTATUS KernelWriteVirtualMemory(PEPROCESS process, PVOID sourceAddress, PVOID targetAddress, SIZE_T size);