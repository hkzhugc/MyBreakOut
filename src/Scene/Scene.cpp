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

Obeject & Scene::getObject(const std::string & name)
{
	return *Objects[name];
}

void Scene::addObeject(const std::string & name, Obeject * obj)
{
	Objects[name] = obj;
}

void Scene::render(const glm::mat4 & view, const glm::mat4& projection)
{
	for (auto& iter : Objects)
	{
		auto obj = iter.second;
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
