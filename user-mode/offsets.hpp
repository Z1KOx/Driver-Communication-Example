struct Offsets
{
	// Head positon
	unsigned long xHeadPos{ 0x4 };
	unsigned long yHeadPos{ 0x8 };
	unsigned long zHeadPos{ 0xC };

	// Normal position
	unsigned long xPos{ 0x34 };
	unsigned long yPos{ 0x38 };
	unsigned long zPos{ 0x3C };

	// View angles
	unsigned long xView{ 0x44 };
	unsigned long yView{ 0x48 };

	// Entity living states
	unsigned long health{ 0xF8 };
	unsigned long armor{ 0xFC };


	// Weapon Ammo
	unsigned long pistolReserve{ 0x114 };
	unsigned long pistolAmmo{ 0x13C };

	unsigned long rifleReserve{ 0x128 };
	unsigned long rifleAmmo{ 0x150 };

	unsigned long grenades{ 0x158 };

	// Objects
	unsigned long localPlayer{ 0x10F4F4 };
	unsigned long entityList{ 0x10F4F8 };
};