#pragma once
#include "../API.h"
class LuaActor : public API
{
public:
	void initFunctions(lua_State* L) override;
};

