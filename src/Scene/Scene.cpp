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

void Scene::render()
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

void Scene::update(float dt)
{
	for (auto& iter : Objects)
	{
		iter.second->update(dt);
	}
}
