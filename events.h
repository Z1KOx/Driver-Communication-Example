#pragma once

#include <ntifs.h>

PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING fullImageName,
	HANDLE processID,
	PIMAGE_INFO imageInfo);