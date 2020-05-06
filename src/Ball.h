#pragma once
#include "SpriteObject.h"
#include "Collision/SphereRigidBody.h"
class Ball
	: public SpriteObject
{
public:
	Ball();
	~Ball();

	virtual void update(float dt);
	SphereRigidBody rigidBody;
	glm::vec2 velocity;
	glm::vec2 screen_bound;
	float radius;
	bool is_stuck;
	bool is_alive;
};

