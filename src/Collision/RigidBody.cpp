#include "RigidBody.h"

Direction VectorClosestDirection(glm::vec3 vec)
{
	float max = 0.f;
	int axis = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (abs(vec[i]) > max)
		{
			axis = i;
			max = abs(vec[i]);
		}
	}
	if (vec[axis] < 0.f)
		axis += 3;
	return static_cast<Direction>(axis);
}
