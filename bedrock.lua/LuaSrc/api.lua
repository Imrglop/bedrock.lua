-- [bedrock.lua MAIN API SCRIPT] --


function constructor_base(body, staticFunctions)
	local __instance = {}
	for k, v in pairs(body) do
		if staticFunctions ~= nil and staticFunctions[k] == true then goto continue end
		if __instance[k] == "new" then goto continue end
		__instance[k] = v
		::continue::
	end
	return __instance
end

function __class(body, staticFunctions)
	body.new = function()
		return constructor_base(body, staticFunctions)
	end
	if body.constructor ~= nil then
		body.new = body.constructor
		body.constructor = nil
	end
	return body
end


__SystemClass = {
	Game = {
		Actor = {
			constructor = function(base)
				local result = constructor_base(System.Actor)
				result.Base = tostring(base)
				return result
			end,
			Base = "0",
			Position = {},
			Rotation = {}
		}
	}
}

System = {}
System.Actor = __class(__SystemClass.Game.Actor)
System.Game = {}
System.Game.AddonEngine = {
	GetForegroundUI = function()
		return __W_GAME_ADDON_ENGINE_GET_FOREGROUND_JSON_UI__()
	end
}
System.Game.GetLocalPlayer = function()
	return System.Actor.new(__W_GAME_LOCALPLAYER_GET_BASE_ADDRESS__())
end
System.Game.LocalPlayer = System.Game.GetLocalPlayer()

System.Keyboard = {
	KeyIsHeld = function(key)
		return __W_KEYBOARD_KEY_IS_HELD__(key)
	end,
	SetKeyState = function(key, state)
		__W_KEYBOARD_SET_KEY_STATE__(key, state)
	end,
	SendKey = function(key)
		System.Keyboard.SetKeyState(key, true)
		System.Keyboard.SetKeyState(key, false)
	end,
	SendKeys = function(keys)
		for i=1,#keys do
			Game.Keyboard.SendKey(keys[i])
		end
	end,
	KeyToChar = function(keyCode)
		return __W_KEYBOARD_KEY_TO_CHAR__(keyCode)
	end,

	OnKeyUpdate = function(keyCode, key) end
}
System.Update = function() end
System.Shutdown = function() end

function System.Actor:IsLoaded()
	return self.Base ~= "0"
end

function System.Actor.Position:SetPosition(x, y, z)
	__W_ACTOR_POSITION_SET__(self.Base, x, y, z)
end

function System.Actor:SetVelocity(x, y, z)
	__W_ACTOR_SET_VELOCITY__(self.Base, x, y, z)
end

function System.Actor:GetName()
	return __W_ACTOR_GET_NAME__(tostring(self.Base))
end