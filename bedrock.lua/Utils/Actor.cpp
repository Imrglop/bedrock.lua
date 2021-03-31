#include "Actor.h"

void* Actor::pass(uintptr_t offset)
{
	return (void*)(this + offset);
}

Vector3* Actor::getPosition() {
	Vector3* pos = (Vector3*)pass(0x4A0);
	return pos;
}

Vector3* Actor::getUpperPosition()
{
	Vector3* pos = (Vector3*)pass(0x4A0 + 12);
	return pos;
}

Vector3* Actor::getVelocity()
{
	return (Vector3*)pass(1244);
}

Rotation* Actor::getRotation()
{
	return (Rotation*)pass(288);
}

const char* Actor::getName()
{
	const char* name = (const char*)pass(0x888);
	return name;
}

const NamespacedID Actor::getIdentifier()
{
	NamespacedID retVal;
	retVal._namespace = (const char*)pass(978);
	retVal.identifier = (const char*)pass(978 + 32);
	return retVal;
}

float* Actor::getAmountTravelled()
{
	return (float*)pass(560);
}