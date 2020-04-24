#pragma once
#include "Scene/Obeject.h"
#include <glm/gtc/matrix_transform.hpp>
class SpriteObject
	: public Obeject
{
public:
	SpriteObject();
	virtual ~SpriteObject();

	virtual void init();
	virtual void render();
	virtual void update(float dt) {} // did nothing
	glm::vec3 color;
	glm::vec2 position;
	glm::vec2 size;
	float angle;
};

