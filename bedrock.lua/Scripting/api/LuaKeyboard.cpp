#include "LuaKeyboard.h"
#include "../../shared.h"
#include "../../main.h"
#include <MinHook.h>

typedef void(*GameKeyPress)(int, int);
GameKeyPress pressGameKey = NULL;

void onKeyPress(int key, int status) {
	bool cancel = (getMods().onKey(key, status));
	if (cancel == false) {
		pressGameKey(key, status);
	}
}

namespace lua_keyboard {
	int keyToChar(lua_State* L) {
		paramCheck(L, 1, "KeyToChar");
		if (!lua_isnumber(L, 1)) {
			luaErr("expected number for KeyToChar");
			return -1;
		}
		int num = (int)lua_tonumber(L, 1);
		std::string str = "";
		std::string ch = str + static_cast<char>(num);
		lua_pushstring(L, ch.c_str());
		return 1;
	}
	int isHeld(lua_State* L) {
		paramCheck(L, 1, "IsHeld");
		if (lua_isstring(L, 1)) {
			auto key_str = lua_tostring(L, 1);
			if (strlen(key_str) != 1) {
				luaErr("expected character for IsHeld, got string");
				return -1;
			}
			int held = keyPressed(*key_str);
			lua_pushboolean(L, held);
			return 1;
		}
		if (lua_isnumber(L, 1)) {
			int key = (int)lua_tonumber(L, 1);
			int held = keyPressed(key);
			lua_pushboolean(L, held);
			return 1;
		}
		luaErr("expected int or character at first parameter of IsHeld");
		return -1;
	}
	int setKeyState(lua_State* L) {
		paramCheck(L, 2, "SetKeyState");
		int keyCode = 0;
		if (lua_isstring(L, 1)) {
			const char* str = lua_tostring(L, 1);
			if (strlen(str) != 1) {
				luaErr("expected character at SetKeyState");
				return -1;
			}
			keyCode = *str;
		}
		else if (lua_isnumber(L, 1)) {
			keyCode = (int)lua_tonumber(L, 1);
		}
		else {
			luaErr("expected character or number as first argument at SetKeyState");
			return -1;
		}
		int keyState = 0;
		if (lua_isboolean(L, 2)) {
			keyState = lua_toboolean(L, 2);
		}
		else if (lua_isnumber(L, 2)) {
			keyState = (int)lua_tonumber(L, 2);
		}
		else {
			luaErr("expected boolean or number as second argument at SetKeyState");
			return -1;
		}
		
		pressGameKey(keyCode, keyState);
		return 1;
	}
};

void LuaKeyboard::initFunctions(lua_State* L)
{
	lua_register(L, "__W_KEYBOARD_KEY_IS_HELD__", lua_keyboard::isHeld);
	lua_register(L, "__W_KEYBOARD_SET_KEY_STATE__", lua_keyboard::setKeyState);
	lua_register(L, "__W_KEYBOARD_KEY_TO_CHAR__", lua_keyboard::keyToChar);
}

void LuaKeyboard::initHooks()
{
	auto gameFunc = getGameFunctions();
	MH_CreateHook(reinterpret_cast<void*>(gameFunc.onKey), onKeyPress, reinterpret_cast<void**>(&pressGameKey));
}
