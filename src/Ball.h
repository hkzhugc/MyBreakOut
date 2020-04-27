#pragma once
#include "SpriteObject.h"
class Ball
	: public SpriteObject
{
public:
	Ball();
	~Ball();

	virtual void update(float dt);

	glm::vec2 velocity;
	glm::vec2 screen_bound;
	float radius;
	bool is_stuck;
};

