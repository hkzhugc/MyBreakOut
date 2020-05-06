#pragma once
#include "SpriteObject.h"
#include "Collision/AABBRigidBody.h"
class Player
	: public SpriteObject
{
public:
	Player();
	~Player();

	virtual void init();
	virtual void update(float dt);
	size_t width;
	glm::vec2 velocity;
	AABBRigidBody rigidBody;
};

