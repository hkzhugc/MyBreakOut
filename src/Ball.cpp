#include "Ball.h"
#include <algorithm>

Ball::Ball()
	: is_stuck(true), is_alive(true), velocity(0, 0)
{
}


Ball::~Ball()
{
}

void Ball::update(float dt)
{
	position += dt * velocity;
	if (!is_stuck)
	{
		if (position.x < size.x) // hit left bound
		{
			velocity.x = -velocity.x;
			position.x = size.x;
		}
		else if (position.x > screen_bound[0] - size.x) // hit right bound
		{
			velocity.x = -velocity.x;
			position.x = screen_bound[0] - size.x;
		}
		if (position.y > screen_bound[1] - size.y) // hit top bound
		{
			velocity.y = -velocity.y;
			position.y = screen_bound[1] - size.y;
		}
		else if (position.y < size.y) // fall into bottom die!
		{
			is_alive = false;
		}
	}
	// TODO : try to use some method to bind the position to the position
	rigidBody.position = glm::vec3(position, 0.f);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.f));
}
