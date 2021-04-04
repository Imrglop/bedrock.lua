#include "Scripting.h"
#include "../shared.h"
#include "../shared_types.h"
#include "Config.h"
#include "doDefaultLua.hpp"
#include "../Utils/Actor.h"
#include <MinHook.h>
#include "API.h"
#include "api/all.h"

#define CURRENT_API_VERSION 1

LuaActor luaActor;
LuaKeyboard luaKeyboard;
LuaAddonEngine luaAddonEngine;
LuaIO luaIO;

std::vector<API*> apis = {
	&luaActor,
	&luaKeyboard,
	&luaAddonEngine,
	&luaIO
};

Scripting::Scripting()
{
}


namespace luaF {
	
}

bool Scripting::loadMod(std::string folderPath)
{
	std::string manifestPath = folderPath + "\\mod_manifest";
	std::ifstream f;

	f.open(manifestPath);
	if (f.fail()) {
		err("No mod manifest detected! Mod path: " << folderPath);
		return false;
	}
	f.close();

	Config manifestFile(manifestPath.c_str(), "");
	if (!(manifestFile.load())) return false;
	std::string modName = manifestFile.getString("name");
	std::string modVersion = manifestFile.getString("version");
	std::string entryPoint = folderPath + "\\" + manifestFile.getString("main");
	int apiVersion = manifestFile.getInteger("api_version");
	bool requireConsole = manifestFile.getBool("require_console");
#pragma region error catching
	if (modName == "null"
		|| modName.size() < 3
		|| modName.size() > 15)
	{
		err("Invalid mod name! Note: The name needs to be 3-15 characters.");
		return false;
	}
	if (modVersion == "null") {
		err("Mod version is not declared!");
		return false;
	}
	if (apiVersion == 0) {
		err("Invalid api version! The newest api version is " << CURRENT_API_VERSION);
		return false;
	}
	if (apiVersion != CURRENT_API_VERSION) {
		err("Outdated mod! Currently, outdated mods are not allowed. This might change in another update. Newest api version is: " << CURRENT_API_VERSION << "\n Received api versoin: " << apiVersion);
		return false;
	}
	for (size_t i = 0; i < entryPoint.size(); i++)
	{
		char ch = entryPoint[i];
		if (ch != '/') continue;
		err("Currently due to security and UWP limitation reasons, you cannot specify directory paths in the 'main' feild. This may change soon.");
		return false;
	}
	if (entryPoint == "null") {
		err("Invalid or no 'main' feild specified. This is where the main script should run. 'luac' or compiled code is recommended.");
		return false;
	}
	if (requireConsole == true) {
		AllocConsole();
	}
#pragma endregion
	lua_State* L = luaL_newstate();
#pragma region libraries, functions
	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);
	luaopen_utf8(L);

	for (size_t i = 0; i < apis.size(); i++) {
		apis[i]->initFunctions(L);
	}
#pragma endregion

	doDefaultLua(L);
	int result = luaL_dofile(L, entryPoint.c_str());
	if (result != LUA_OK) {
		err(lua_tostring(L, -1));
		return false;
	}
	this->loadedScripts.insert({ entryPoint, L });
	this->modNames.insert({ L, modName });
	llog("Loaded mod " << modName);
	return true;
}

bool Scripting::loadMods(string gameData)
{
	string modsDir = gameData + "mods";
	if (!(CreateDirectoryA(modsDir.c_str(), NULL))) {
		if (GetLastError() != ERROR_ALREADY_EXISTS)
		{
			err("Couldn't make mods directory at '" << gameData << "'!");
			return false;
		}
	}
	else {
		llog("Mods directory created: " << modsDir);
	}
	// TODO: loop through dir
	loadMod(modsDir + "\\test");
	return true;
}

void Scripting::unloadScript(std::string path)
{
	lua_State* state = this->loadedScripts.at(path);
	lua_close(state);
	this->loadedScripts.erase(path);
}

void Scripting::updateMods()
{
	for (std::map<std::string, lua_State*>::iterator it = this->loadedScripts.begin(); it != this->loadedScripts.end(); ++it)
	{
		lua_State* L = it->second;
		lua_getglobal(L, "System");
		if (lua_istable(L, -1)) {
			lua_pushstring(L, "Update");
			lua_gettable(L, -2);

			if (lua_isfunction(L, -1)) { // if System.Update is a function...
				int result = lua_pcall(L, 0, 0, 0); // call it with 0 args, 0 results, and error handling 0
				if (result != 0) {
					const char* err = lua_tostring(L, -1);
					luaErr(err);
				}
			}
		}
	}
}

void Scripting::initHooks()
{
	auto gameFunc = getGameFunctions();
	luaKeyboard.initHooks();
}

bool Scripting::onKey(int keyCode, int status)
{
	for (std::map<std::string, lua_State*>::iterator it = this->loadedScripts.begin(); it != this->loadedScripts.end(); ++it)
	{
		// TODO: add listener system
		lua_State* L = it->second;
		lua_getglobal(L, "System");
		if (lua_istable(L, -1)) {
			lua_pushstring(L, "Keyboard");
			lua_gettable(L, -2);
			if (lua_istable(L, -1)) { // if System.Keyboard is a table...
				lua_pushstring(L, "OnKeyUpdate");
				lua_gettable(L, -2);
				if (lua_isfunction(L, -1)) {
					// OnKeyUpdate is a function
					lua_pushnumber(L, keyCode);
					lua_pushnumber(L, status);
					int result = lua_pcall(L, 2, 1, 0); // call OnKeyUpdate with 2 args, 1 result, and error handling 0
					if (result != 0) {
						const char* err = lua_tostring(L, -1);
						luaErr(err);
					}
					else {
						std::string ret(lua_tostring(L, -1));
						if (ret == "CANCEL") {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void Scripting::unloadMods()
{
	// FIXME: crash
	llog("Unloading Mods");
	for (std::map<std::string, lua_State*>::iterator it = this->loadedScripts.begin(); it != this->loadedScripts.end(); ++it)
	{
		unloadScript(it->first);
	}
}