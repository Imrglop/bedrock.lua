#pragma once

#include <map>
#include <string>

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

class Scripting
{
private:
	std::map<std::string, lua_State*> loadedScripts;
public:
	Scripting();
	bool loadMod(std::string folderPath);
	bool loadMods(std::string gameData);
	void unloadMods();
	void unloadScript(std::string path);
	void updateMods();
	void initHooks();
	bool onKey(int keyCode, int status);
	std::map<lua_State*, std::string> modNames;
};