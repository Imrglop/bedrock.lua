#include "LuaAddonEngine.h"
#include "../../Utils/memory.h"
#include "../../shared.h"

namespace lua_addon_engine {
	const char* JsonUI = (const char*)(memory::getMLPtrAddy(_moduleBase() + 0x03787148, {}) + 0xAEBC + 1048);
	std::string trimJsonUI() {
		const auto len = strlen(JsonUI);
		std::string ret = std::string(JsonUI);
		for (size_t i = 0; i < len; i++)
		{
			if (JsonUI[i] == '\n') {
				ret[i] = '\0';
				break;
			}
		}
		return ret;
	}
	int getJsonUI(lua_State* L)
	{
		lua_pushstring(L, trimJsonUI().c_str());
		return 1;
	}
}

void LuaAddonEngine::initFunctions(lua_State* L) {
	lua_register(L, "__W_GAME_ADDON_ENGINE_GET_FOREGROUND_JSON_UI__", lua_addon_engine::getJsonUI);
}
