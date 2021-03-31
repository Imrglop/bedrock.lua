#pragma once
#include "../API.h"
class LuaAddonEngine : public API
{
public:
	void initFunctions(lua_State* L);
};

