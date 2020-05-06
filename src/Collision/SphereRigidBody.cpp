#pragma once
#include "RigidBody.h"
#include "SphereRigidBody.h"
#include "AABBRigidBody.h"

Collision SphereRigidBody::checkCollision(const AABBRigidBody& rhs)
{
	auto diff = position - rhs.position;
	auto half_size = rhs.size / 2.0f;
	auto clamped = glm::clamp(diff, -half_size, half_size);
	auto closest = rhs.position + clamped;
	diff = position - closest;
	float offset = radius - glm::length(diff);
	return std::make_tuple(offset > 0,
		                   VectorClosestDirection(diff),
		                   offset * glm::normalize(diff));
}
