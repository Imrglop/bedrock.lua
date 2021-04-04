#pragma once
class HookBase
{
public:
	HookBase(const char* name);
	virtual void enableHook();
	const char* hookName = "default-hook";
};

inline HookBase::HookBase(const char* name) {
	this->hookName = name;
}