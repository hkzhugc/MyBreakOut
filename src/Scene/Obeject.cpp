#include "Obeject.h"



Obeject::Obeject()
	: parent(nullptr), shader(nullptr), mesh(nullptr), ubo4ViewProject(0)
{
}


Obeject::~Obeject()
{
}

glm::mat4 Obeject::world()
{
	if (parent)
		return parent->world() * model;
	else
		return model;
}

// require : must be call after shader use
void Obeject::bindTextures()
{
	assert(shader && textures.size()); // TODO : or raise exception?
	//shader->use();
	int cnt = 0;
	for (auto iter : textures)
	{
		shader->setInt(iter.first, cnt);
		iter.second->bindUnit(cnt);
		cnt++;
	}
}
