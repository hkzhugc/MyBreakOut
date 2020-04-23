#include "Player.h"

const float PLAYER_VELOCITY(500.0f);

Player::Player()
{
}


Player::~Player()
{
}

void Player::update(float dt)
{
	// update position
	if (direction)
	{
		position += direction * dt * glm::vec2(PLAYER_VELOCITY, 0.f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(size, 1.f));
	}
}
