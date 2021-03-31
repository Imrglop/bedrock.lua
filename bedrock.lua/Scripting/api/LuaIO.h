#pragma once
#include "../API.h"
class LuaIO : public API
{
public:
	void initFunctions(lua_State* L) override;
};

