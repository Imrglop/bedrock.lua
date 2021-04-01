#include "LuaIO.h"

namespace lua_io {
	int printRaw(lua_State* L) {
		int args = lua_gettop(L);
		for (int i = 0; i < args; ++i) {
			std::cout << lua_tostring(L, i);
		}
		return 1;
	}
	int errRaw(lua_State* L) {
		int args = lua_gettop(L);
		for (int i = 0; i < args; ++i) {
			std::cerr << lua_tostring(L, i);
		}
		return 1;
	}
	int input(lua_State* L) {
		int args = lua_gettop(L);
		for (int i = 0; i < args; ++i) {
			std::cout << lua_tostring(L, i);
		}
		const char* line = "";
		std::cin.getline((char*)line, 0xff);
		lua_pushstring(L, line);
		return 1;
	}
}

void LuaIO::initFunctions(lua_State* L)
{
	lua_register(L, "__W_LUA_IO_PRINT_RAW__", lua_io::printRaw);
	lua_register(L, "__W_LUA_IO_ERR_RAW__", lua_io::errRaw);
	lua_register(L, "__W_LUA_IO_INPUT__", lua_io::input);
}
