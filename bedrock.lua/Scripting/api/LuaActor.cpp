#include "LuaActor.h"
#include "../../Utils/Actor.h"
#include "../../shared.h"

namespace lua_actor {
	int getLocalPlayerBase(lua_State* L) {
		auto lpPlayer = getLocalPlayer();
		lua_pushstring(L, std::to_string(lpPlayer).c_str());
		return 1;
	}

	int addVel(lua_State* L) {
		paramCheck(L, 4, "AddVelocity");
		Actor* lpActor = getActor(L);
		Vector3* vel = lpActor->getVelocity();
		vel->x += (float)lua_tonumber(L, 2);
		vel->y += (float)lua_tonumber(L, 3);
		vel->z += (float)lua_tonumber(L, 4);
		return 1;
	}

	int setVel(lua_State* L) {
		paramCheck(L, 1, "SetVelocity");
		Actor* lpActor = getActor(L);
		Vector3* vel = lpActor->getVelocity();
		if (!lua_isnil(L, 2))
			vel->x = (float)lua_tonumber(L, 2);
		if (!lua_isnil(L, 3))
			vel->y = (float)lua_tonumber(L, 3);
		if (!lua_isnil(L, 4))
			vel->z = (float)lua_tonumber(L, 4);
		return 1;
	}

	int getYaw(lua_State* L) {
		paramCheck(L, 1, "GetYaw");
		Actor* lpActor = getActor(L);
		Vector3* vel = lpActor->getVelocity();
		lua_pushnumber(L, lpActor->getRotation()->yaw);
		return 1;
	}

	int getPitch(lua_State* L) {
		paramCheck(L, 1, "GetPitch");
		Actor* lpActor = getActor(L);
		Vector3* vel = lpActor->getVelocity();
		lua_pushnumber(L, lpActor->getRotation()->pitch);
		return 1;
	}

	int getName(lua_State* L) {
		paramCheck(L, 1, "GetName");
		Actor* lpActor = getActor(L);
		auto str = lpActor->getName();
		lua_pushstring(L, str);
		return 1;
	}
}

void LuaActor::initFunctions(lua_State* L)
{
	lua_register(L, "__W_GAME_LOCALPLAYER_GET_BASE_ADDRESS__", lua_actor::getLocalPlayerBase);
	lua_register(L, "__W_ACTOR_ADD_VELOCITY__", lua_actor::addVel);
	lua_register(L, "__W_ACTOR_SET_VELOCITY__", lua_actor::setVel);
	lua_register(L, "__W_ACTOR_ROTATION_GET_YAW__", lua_actor::getYaw);
	lua_register(L, "__W_ACTOR_ROTATION_GET_PITCH__", lua_actor::getPitch);
	lua_register(L, "__W_ACTOR_GET_NAME__", lua_actor::getName);
}
