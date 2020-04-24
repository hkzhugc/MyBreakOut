#pragma once
#include <map>
#include <string>
#include "Obeject.h"
class Scene
{
public:
	Scene();
	~Scene();
	Obeject& getObject(const std::string& name);
	void addObeject(const std::string& name, Obeject* obj);
	void render();
	void init();
	void update(float dt);
private:
	std::map<std::string, Obeject*> Objects;
};

