#include <iostream>
#include "kernelInterface.hpp"
#include "offsets.hpp"

int main()
{
	// Create an instance of KernelInterface, which connects to the driver via the specified path.
	KernelInterface driver("\\\\.\\Z1KODriver");

	// Retrieve the executable address from the driver.
	const ULONG address = driver.getExecutableAddress();
	const ULONG procID = driver.getProcessID();

	std::puts("AssaultCube 1.2.0.2");
	std::cout << "Address: 0x" << std::hex << address << '\n';
	std::cout << "ProcessID: " << std::dec << procID << '\n';

	const Offsets offset;

	if (procID)
	{
		uint32_t localPlayerAddress = driver.ReadVirtualMemory<uint32_t>(procID, address + offset.localPlayer, sizeof(uint32_t));
		driver.writeVirtualMemory(procID, localPlayerAddress + offset.health, 1337, sizeof(offset.health));
	}

	system("pause>nul");
	return 0;
}