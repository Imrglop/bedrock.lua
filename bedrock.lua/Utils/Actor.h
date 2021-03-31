#pragma once
#include <cstdint>

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Rotation {
	float pitch;
	float yaw;
};

struct NamespacedID {
	const char* _namespace;
	const char* identifier;
};

class Actor {
public:
	void* pass(uintptr_t offset);
	Vector3* getPosition();
	Vector3* getUpperPosition();
	Vector3* getVelocity();
	Rotation* getRotation();
	const char* getName();
	const NamespacedID getIdentifier();
	float* getAmountTravelled();
};