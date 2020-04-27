#pragma once
#include "Scene/Obeject.h"
#include "SpriteObject.h"
class GameLevel
	: public Obeject
{
public:
	GameLevel();
	virtual ~GameLevel();

	bool loadLevel(const std::string& path, size_t level_width, size_t level_height);

	virtual void init();
	virtual void render();
	virtual void update(float dt);

	glm::vec2 position;
private:
	size_t levelWidth, levelHeight;
	std::vector<std::vector<int>> tileDatas;
};