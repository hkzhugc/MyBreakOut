#pragma once
#include "SpriteObject.h"
class Player
	: public SpriteObject
{
public:
	Player();
	~Player();

	void update(float dt);
	size_t width;
	glm::vec2 velocity;
};

