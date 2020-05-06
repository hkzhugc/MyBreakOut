#pragma once
#include <glm/glm.hpp>
#include <tuple>

class AABBRigidBody;
class SphereRigidBody;

// first check which axis is the max, x=>0 y=>1, z=>2
// second if is negetive, add 3
enum class Direction
{
	RIGHT = 1,
	UP,
	FRONT,
	LEFT,
	DOWN,
	BACK
};
Direction VectorClosestDirection(glm::vec3 vec);
typedef std::tuple<bool, Direction, glm::vec3> Collision;