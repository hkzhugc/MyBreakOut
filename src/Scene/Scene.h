#pragma once
#include <map>
#include <string>
#include "SceneObeject.h"
class Scene
{
public:
	Scene();
	~Scene();
	SceneObeject& getObject(const std::string& name);
	void addObeject(const std::string& name, SceneObeject* obj);
	void render(const glm::mat4& view, const glm::mat4& projection);
	void init();
private:
	std::map<std::string, SceneObeject*> Objects;
};

