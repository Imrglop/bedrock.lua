#include "memory.h"

uintptr_t memory::getMLPtrAddy(uintptr_t address, std::vector<DWORD> offsets)
{
	uintptr_t ptrPoint = address + 0;
	MEMORY_BASIC_INFORMATION info;
	VirtualQuery((void*)ptrPoint, &info, sizeof(info));
	if (!(info.Protect & PAGE_READWRITE)) {
		return NULL;
	}
	ptrPoint = *(uintptr_t*)ptrPoint;

	for (uint32_t i = 0; i < offsets.size(); i++)
	{
		auto newPtrPoint = getMLPtrAddy(ptrPoint + offsets[i], {});
		if (newPtrPoint == NULL) return NULL;
		ptrPoint = newPtrPoint;
	}
	return ptrPoint;
};
