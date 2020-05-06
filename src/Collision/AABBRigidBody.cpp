#pragma once
#include "RigidBody.h"
#include "AABBRigidBody.h"

bool AABBRigidBody::checkCollision(const AABBRigidBody& rhs)
{
	bool flag = true;
	for (size_t axis = 0; axis < 3 && flag; axis++)
	{
		bool collision = position[axis] + size[axis] / 2 >= rhs.position[axis] - rhs.size[axis] / 2 &&
			rhs.position[axis] + rhs.size[axis] / 2 >= position[axis] - size[axis] / 2;
		flag = flag && collision;
	}
	return flag;
}