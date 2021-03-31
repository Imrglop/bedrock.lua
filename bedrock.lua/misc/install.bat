@echo off
title bedrock.lua Porter-Installer

color a

set _path="%localappdata%\Packages\Microsoft.MinecraftUWP_8wekyb3d8bbwe\AC\bedrock.lua"
echo It will "install" bedrock.lua on %_path%
echo This will be required otherwise mod running will be corrupted.
echo.
echo Continue?
pause >nul

@del /q "%_path%\data"

move ".\data" "%_path%\data"
move ".\bedrock.lua.dll" "%_path%\bedrock.lua.dll"