#include "main.h"
#include "shared.h"
#include "Sig/SignatureScanner.h"
#include <Psapi.h>
#include <chrono>
#include <MinHook.h>
#include "Utils/Utils.h"

int* keys;

GameFunc gameFunc;

namespace gameInfo {
    uintptr_t base;
    uintptr_t funcEnd;
}

uintptr_t _moduleBase() {
    return gameInfo::base;
}

#pragma region Console Files
FILE* pCout;
FILE* pCin;
#pragma endregion

Scripting mods;

Scripting getMods() {
    return mods;
}

#define MS(x) std::chrono::duration_cast<std::chrono::milliseconds>(x##.time_since_epoch()).count()
#define DATE_NOW() std::chrono::system_clock::now()


GameFunc getGameFunctions()
{
    return gameFunc;
}

uintptr_t slide(uintptr_t address) {
	return gameInfo::base + address;
}

int keyPressed(int offset)
{
    return keys[offset];
}

void scanSigs() {
    const auto ms = DATE_NOW();
    MODULEINFO info;
    GetModuleInformation(GetCurrentProcess(), (HMODULE)gameInfo::base, &info, sizeof(MODULEINFO));
    SignatureScanner mainScanner(gameInfo::base);
    gameFunc.hurtTime = mainScanner.scan("c7 86 ? ? ? ? ? ? ? ? c7 86 ? ? ? ? ? ? ? ? c7 86 ? ? ? ? ? ? ? ? 89 8e");
    uintptr_t sigKeys = (mainScanner.scan("48 8d 0d ? ? ? ? 89 1c b9"));
    gameFunc.onKey = mainScanner.scan("48 89 5c 24 ? 57 48 83 ec ? 8b 05 ? ? ? ? 8b da");
    

    int off = *(int*)(sigKeys + 0x3);
    uintptr_t off2 = sigKeys - gameInfo::base + off + 0x7;
    keys = (int*)(gameInfo::base + off2);
    llog("Key map: " << keys);
    llog("Key hook: " << reinterpret_cast<void*>(gameFunc.onKey));
    llog("HT: " << reinterpret_cast<void*>(gameFunc.hurtTime));
}

void _dllExit(HMODULE hModule, DWORD dwExitCode) {
    if (pCout != NULL) fclose(pCout);
    if (pCin != NULL) fclose(pCin);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

int __stdcall init(HMODULE hModule) 
{
    llog("Initializing..");
    scanSigs();
    llog("Done! Thread: " << GetCurrentThreadId());
    SetConsoleTitle(TEXT("bedrock.lua"));
#pragma warning(disable : 4996)
    std::string appdata(getenv("localappdata"));
    appdata = utils::getParentFolderOf(appdata);

    MH_Initialize();
    llog("Creating Hooks");
    mods.initHooks();
    MH_EnableHook(MH_ALL_HOOKS);
    llog("Loading Mods");
    mods.loadMods(appdata);
    llog("Mods loaded.");

    while (true) {
        Sleep(17);
        if (GetAsyncKeyState(VK_ESCAPE) & 1)
        {
            break;
        }
        mods.updateMods();
    }
    MH_Uninitialize();
    Sleep(300); // wait for threads
    _dllExit(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
#pragma region Console Init
        AllocConsole();
        freopen_s(&pCout, "CONOUT$", "w", stdout);
        freopen_s(&pCin, "CONIN$", "r", stdin);
#pragma endregion
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
        gameInfo::base = (uintptr_t)GetModuleHandle(NULL);
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
    }
    return TRUE;
}