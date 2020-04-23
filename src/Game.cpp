#include "Game.h"
#include "Resources/ResourceManager.h"

Game::Game(size_t width, size_t height)
	: Width(width), Height(height), player(nullptr)
{
}


Game::~Game()
{
}

void Game::init()
{
	State = GAME_ACTIVE;
	// load resouces
	//ResourceManager::LoadShader("sprite", "../shader/2Dtexture.vs", "../shader/2Dtexture.fs", "");
	//ResourceManager::LoadTexture2D("block", "../texture/block.png");
	//ResourceManager::LoadTexture2D("mario", "../texture/mario.png");
	//ResourceManager::LoadTexture2D("solid-block", "../texture/solid-block.png");
	//ResourceManager::AddDefaultMesh("sprite_quad", QUAD);
	//// new a player
	//player = new Player();
	//player->size = glm::vec2(100, 20);
	//player->position = glm::vec2(Width / 2.f, player->size.y / 2);
	//player->shader = ResourceManager::GetShader("sprite");
	//player->mesh = ResourceManager::GetMesh("sprite_quad");
	//player->textures["image"] = ResourceManager::GetTexture2D("mario");
}

void Game::render()
{
}
