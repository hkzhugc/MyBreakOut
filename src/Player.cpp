#include "Player.h"
#include <algorithm>
Player::Player()
{
}


Player::~Player()
{
}

void Player::update(float dt)
{
	// update position
	position += dt * velocity;
	position.x = std::max(std::min(width - size.x, position.x), size.x);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.f));
}
