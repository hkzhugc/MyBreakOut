#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
	for (auto& iter : Objects)
	{
		delete iter.second;
	}
	Objects.clear();
}

SceneObeject & Scene::getObject(const std::string & name)
{
	return *Objects[name];
}

void Scene::addObeject(const std::string & name, SceneObeject * obj)
{
	Objects[name] = obj;
}

void Scene::render(const glm::mat4 & view, const glm::mat4& projection)
{
	for (auto& iter : Objects)
	{
		auto obj = iter.second;
		if (obj->shader && obj->mesh && obj->texture)
		{
			obj->shader->use();
			// set mvp first
			obj->shader->setMat4("view", view);
			obj->shader->setMat4("projection", projection);
			obj->shader->setMat4("model", obj->model_mat);
			// TODO : each obj should have a method to auto config shader uniform values by a map ?
			obj->shader->setInt("texture", 0); // set texture
			glBindTextureUnit(0, obj->texture->getID()); // TODO : don't want to see opengl code 
			obj->mesh->draw();
		}
	}
}
