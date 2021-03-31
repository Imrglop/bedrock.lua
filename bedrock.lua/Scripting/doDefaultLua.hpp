#pragma once
#include "../log.h"
#include "API.h"
#include "../Utils/Utils.h"

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

char* dllPath = new char[_MAX_PATH];

int doDefaultLua(lua_State* L) {
	GetModuleFileNameA(GetModuleHandleW(L"bedrock.lua.dll"), dllPath, _MAX_PATH);
	std::string _str(dllPath);
	std::string strPath = utils::getParentFolderOf(_str) + "\\api.out";
	int res = luaL_dofile(L, strPath.c_str());
	if (res != LUA_OK) {
		err(lua_tostring(L, -1));
	}
	return res;
}