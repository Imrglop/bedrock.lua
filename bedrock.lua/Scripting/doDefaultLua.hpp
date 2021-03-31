#pragma once
#include "../log.h"
#include "API.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

char* dllPath = new char[_MAX_PATH];

std::string getParentFolderOf(std::string in, int purgeAmount = 0, char ch1 = '\\', char ch2 = '/') {
	std::string str(in);
	int amountOfSlash = 0;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == ch1 || str[i] == ch2) {
			amountOfSlash++;
		}
	}

	if (str[str.size() - 1] == ch1 || str[str.size() - 1] == ch2) amountOfSlash--;

	int a2 = 0;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == ch1 || str[i] == ch2) {
			a2++;
			if (amountOfSlash - a2 == purgeAmount) {
				str[i] = '\0';
				return str.c_str();
			}
		}
	}
	return "";
}

int doDefaultLua(lua_State* L) {
	GetModuleFileNameA(GetModuleHandleW(L"bedrock.lua.dll"), dllPath, _MAX_PATH);
	std::string _str(dllPath);
	std::string strPath = getParentFolderOf(_str) + "\\api.out";
	int res = luaL_dofile(L, strPath.c_str());
	if (res != LUA_OK) {
		err(lua_tostring(L, -1));
	}
	return res;
}