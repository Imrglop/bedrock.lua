#pragma once

#include <Windows.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <map>
#include <fstream>
#include "Utils/memory.h"

#include "log.h"

struct GameFunc {
    uintptr_t hurtTime;
    uintptr_t onKey;
};

GameFunc getGameFunctions();

uintptr_t slide(uintptr_t address);
#define getLocalPlayer() memory::getMLPtrAddy(slide(0x03B5B318), { 0x0, 0x20, 0xC8, 0x358, 0x58, 0x0 })

int keyPressed(int offset);
uintptr_t _moduleBase();
void _dllExit(HMODULE hModule, DWORD dwExitCode);
