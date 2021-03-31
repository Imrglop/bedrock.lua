#pragma once
#ifndef HOOK_H
#define HOOK_H
#include <Windows.h>
#include <vector>
namespace hook {
	void NOPBytes(DWORD_PTR staticAddy, UINT amount);
	void writeBytes(DWORD_PTR staticAddy, std::vector<unsigned char> bytes);
};
#endif