#pragma once
#include "Scene/SceneObeject.h"
#include <glm/gtc/matrix_transform.hpp>
class SpriteObject
	: public SceneObeject
{
public:
	SpriteObject();
	~SpriteObject();

	virtual void init();
	virtual void render();
	//virtual void update();

	glm::vec2 position;
	glm::vec2 size;
	float angle;
};

