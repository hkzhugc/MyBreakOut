#include "SpriteObject.h"



SpriteObject::SpriteObject()
	: position(0.f, 0.f), size(1.f, 1.f), angle(0.f), color(1.f, 1.f, 1.f)
{
}


SpriteObject::~SpriteObject()
{
}

void SpriteObject::init()
{
	// TODO : raise init failed exception
	assert(shader && mesh && textures.size());
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
	shader->bindUniformMatrices(ubo4ViewProject);
	shader->setMat4("model", world());
	shader->setVec3("color", color);
	bindTextures();
	mesh->draw();
}
