#pragma once

#include <Windows.h>
#include <vector>

namespace memory
{
	uintptr_t getMLPtrAddy(uintptr_t address, std::vector<DWORD> offsets);
};

