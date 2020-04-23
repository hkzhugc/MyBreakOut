#pragma once
#include "SpriteObject.h"
class Player
	: public SpriteObject
{
public:
	Player();
	~Player();

	void update(float dt);
	int direction;
};

