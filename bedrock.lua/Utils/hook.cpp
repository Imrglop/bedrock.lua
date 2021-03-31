#include "hook.h"
#include <iostream>

void hook::NOPBytes(DWORD_PTR staticAddy, UINT amount)
{
	try {
		DWORD oldVP;
		VirtualProtect((byte*)staticAddy, (DWORD_PTR)amount, PAGE_EXECUTE_READWRITE, &oldVP);
		for (UINT i = 0; i < amount; i++) {
			byte* writeTo = (byte*)(staticAddy + i);
			*writeTo = (byte)0x90;
		}
		VirtualProtect((byte*)staticAddy, (DWORD_PTR)amount, oldVP, &oldVP);
	}
	catch (std::exception e)
	{
		std::cout << "Error: " << e.what() << '\n';
	}
	
}

void hook::writeBytes(DWORD_PTR staticAddy, std::vector<unsigned char> bytes)
{
	DWORD oldVP;
	VirtualProtect((byte*)staticAddy, (DWORD_PTR)bytes.size(), PAGE_EXECUTE_READWRITE, &oldVP);
	for (UINT i = 0; i < bytes.size(); i++) {
		byte* writeTo = (byte*)(staticAddy + i); // the byte pointer to write to..
		*writeTo = bytes[i];
	}
	VirtualProtect((byte*)staticAddy, (DWORD_PTR)bytes.size(), oldVP, &oldVP);
}