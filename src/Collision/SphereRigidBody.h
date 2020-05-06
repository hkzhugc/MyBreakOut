#pragma once
#include "RigidBody.h"
class SphereRigidBody
{
public:
	Collision checkCollision(const AABBRigidBody& rhs);
	glm::vec3 position;
	float radius;
};

