#pragma once
#include "RigidBody.h"
class AABBRigidBody
{
public:
	bool checkCollision(const AABBRigidBody& rhs);
	glm::vec3 position;
	glm::vec3 size;
};