#include "GameLevel.h"
#include "Resources/ResourceManager.h"
#include <fstream>
#include <sstream>
using namespace std;
GameLevel::GameLevel()
	: position(0.f, 0.f)
{
}

GameLevel::~GameLevel()
{
	for (auto c : childrens)
	{
		if (c != nullptr)
			delete c;
	}
	childrens.clear();
}

bool GameLevel::loadLevel(const std::string & path, size_t level_width, size_t level_height)
{
	ifstream level_file(path);
	if (!level_file.is_open())
		return false;
	levelWidth = level_width;
	levelHeight = level_height;
	string line;
	while (getline(level_file, line))
	{
		stringstream ss(line);
		vector<int> row_data;
		int code;
		while (ss >> code)
			row_data.push_back(code);
		tileDatas.push_back(row_data);
	}
	return true;
}

void GameLevel::init()
{
	assert(tileDatas.size());
	assert(tileDatas[0].size());
	size_t rows = tileDatas.size();
	size_t cols = tileDatas[0].size();
	float unit_height = static_cast<float>(levelHeight) / rows;
	float unit_width  = static_cast<float>(levelWidth)  / cols;
	glm::vec2 unit_offset(unit_width, unit_height);
	glm::vec2 offset(cols * -0.5f * unit_width, rows * -0.5f * unit_height); // from world center to left coord
	auto solid_block_texture = ResourceManager::GetTexture2D("solid-block");
	auto block_texture = ResourceManager::GetTexture2D("block");
	auto shader        = ResourceManager::GetShader("sprite");
	auto block_mesh    = ResourceManager::GetMesh("sprite_quad");
	model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.f));
	for (size_t y = 0; y < rows; y++)
	{
		for (size_t x = 0; x < cols; x++)
		{
			int code = tileDatas[rows - 1 - y][x];
			if (code == 0)
				continue;
			glm::vec2 pos = glm::vec2(x + 0.5f, y + 0.5f) * unit_offset;
			glm::vec2 size = unit_offset * 0.5f;
			SpriteObject* obj = new SpriteObject();
			obj->ubo4ViewProject = ubo4ViewProject;
			obj->position = pos;
			obj->size = size;
			obj->shader = shader;
			obj->mesh = block_mesh;
			obj->parent = this;
			switch (code)
			{
			case 1:
				obj->color = glm::vec3(0.8f, 0.8f, 0.7f);
				obj->textures["image"] = solid_block_texture;
				break;
			case 2:
				obj->color = glm::vec3(0.2f, 0.6f, 1.0f);
				obj->textures["image"] = block_texture;
				break;
			case 3:
				obj->color = glm::vec3(0.0f, 0.7f, 0.0f);
				obj->textures["image"] = block_texture;
				break;
			case 4:
				obj->color = glm::vec3(0.8f, 0.8f, 0.4f);
				obj->textures["image"] = block_texture;
				break;
			case 5:
				obj->color = glm::vec3(1.0f, 0.5f, 0.0f);
				obj->textures["image"] = block_texture;
				break;
			default:
				// TODO : raise exception
				break;
			}
			obj->init();
			childrens.push_back(obj);
		}
	}
}

void GameLevel::render()
{
	for (auto children : childrens)
	{
		children->render();
	}
}
