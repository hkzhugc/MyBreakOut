#include "Brick.h"

void Brick::init()
{
	SpriteObject::init();
	auto&& parent_world = parent ? parent->world() : glm::mat4(1.0f);
	rigidBody.position = parent_world * glm::vec4(position, 0.f, 1.0f);
	rigidBody.size = glm::vec3(size, 0) * 2.0f;
}
