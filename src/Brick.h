#pragma once
#include "SpriteObject.h"
#include "Collision/AABBRigidBody.h"
class Brick
	: public SpriteObject
{
public:
	AABBRigidBody rigidBody;
	virtual void init();
	virtual void update(float dt) {}
};

