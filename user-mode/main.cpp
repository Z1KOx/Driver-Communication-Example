#include <iostream>
#include "kernelInterface.hpp"

int main()
{
	// Create an instance of KernelInterface, which connects to the driver via the specified path.
	KernelInterface driver = KernelInterface("\\\\.\\Z1KODriver");

	// Retrieve the executable address from the driver.
	ULONG address = driver.getExecutableAddress();

	std::cout << address << '\n';

	while (true)
	{

	}
}