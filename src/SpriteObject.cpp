#include "SpriteObject.h"



SpriteObject::SpriteObject()
	: position(0, 0), size(1, 1), angle(0)
{
}


SpriteObject::~SpriteObject()
{
}

void SpriteObject::init()
{
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position, 0.f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, 1.f));
	shader->use();
	shader->setInt("image", 0); // set texture
}

void SpriteObject::render()
{
	shader->use();
	shader->setMat4("model", model);
	glBindTextureUnit(0, texture->getID()); // TODO : don't want to see opengl code
	mesh->draw();
}
