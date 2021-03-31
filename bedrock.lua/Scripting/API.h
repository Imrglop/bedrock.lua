#pragma once
#include "../log.h"
#include "../Utils/Actor.h"

#define luaErr(msg) LOGX("ScriptError", msg)
#define paramCheck(L, amt, func) if (lua_gettop(L) < amt) {err("[ScriptError] expected " << amt << " argument(s) on " << func); return -1;}

// Include lua libraries
extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

class API
{
private:
public:
	virtual void initFunctions(lua_State* L);
};

inline void API::initFunctions(lua_State* L) {
	llog("(default init functions call)");
}

inline Actor* getActor(lua_State* L) {
	const char* str = lua_tostring(L, 1);
	Actor* actor = (Actor*)std::stoull(str);
	return actor;
};
