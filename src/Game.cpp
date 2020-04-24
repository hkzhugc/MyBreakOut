#include "Game.h"
#include "Resources/ResourceManager.h"
const float PLAYER_VELOCITY(500.0f);

Game::Game(size_t width, size_t height)
	: Width(width), Height(height), player(nullptr)
{
	memset(Keys, 0, sizeof(Keys));
}


Game::~Game()
{
}

void Game::init()
{
	State = GAME_ACTIVE;
	// check resouces
	//ResourceManager::LoadShader("sprite", "../shader/2Dtexture.vs", "../shader/2Dtexture.fs", "");
	//ResourceManager::LoadTexture2D("block", "../texture/block.png");
	//ResourceManager::LoadTexture2D("mario", "../texture/mario.png");
	//ResourceManager::LoadTexture2D("solid-block", "../texture/solid-block.png");
	//ResourceManager::AddDefaultMesh("sprite_quad", QUAD);
	// new a player
	player = new Player();
	player->size = glm::vec2(70, 15);
	player->position = glm::vec2(Width / 2.f, player->size.y);
	player->width = Width;
	player->shader = ResourceManager::GetShader("sprite");
	player->mesh = ResourceManager::GetMesh("sprite_quad");
	player->textures["image"] = ResourceManager::GetTexture2D("block");
	// new a ball
	ball = new Ball();
	ball->size = glm::vec2(10, 10);
	ball->position = player->position + glm::vec2(0, player->size.y + ball->size.y);
	ball->velocity = glm::vec2(500, 300);
	ball->screen_bound = glm::vec2(Width, Height);
	ball->shader = ResourceManager::GetShader("sprite");
	ball->mesh = ResourceManager::GetMesh("sprite_quad");
	ball->textures["image"] = ResourceManager::GetTexture2D("block");

	// new a game level
	level = new GameLevel();
	size_t level_width = Width;
	size_t level_height = Height / 2;
	level->loadLevel("../level/level1.txt", level_width, level_height);
	level->position = glm::vec2(0.f, Height - level_height);
}

void Game::processInput()
{
	if (State == GAME_ACTIVE)
	{
		if (Keys[GLFW_KEY_A] && !Keys[GLFW_KEY_D])
		{
			player->velocity.x = -PLAYER_VELOCITY;
		}
		else if (!Keys[GLFW_KEY_A] && Keys[GLFW_KEY_D])
		{
			player->velocity.x = PLAYER_VELOCITY;
		}
		else
		{
			player->velocity.x = 0;
		}
	}
}

void Game::update(float dt)
{
	player->update(dt);
	//level->update(dt);
}

void Game::render()
{
}
