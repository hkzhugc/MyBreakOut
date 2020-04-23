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
		obj->shader->use();
		// set view and projection, since they are invisible to object
		obj->shader->setMat4("view", view);
		obj->shader->setMat4("projection", projection);
		// call object render function
		obj->render();
	}
}

void Scene::init()
{
	for (auto& iter : Objects)
	{
		iter.second->init();
	}
}
