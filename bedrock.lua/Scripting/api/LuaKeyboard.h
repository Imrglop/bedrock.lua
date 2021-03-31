#pragma once
#include "../API.h"

class LuaKeyboard : public API
{
public:
	void initFunctions(lua_State* L) override;
	void initHooks();
};

