#include "Game.h"
#include "Resources/ResourceManager.h"
#include <algorithm>
const glm::vec2 PLAYER_VELOCITY(500.0f, 200.f);

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
	ball->rigidBody.radius = 10.f;
	//ball->velocity = glm::vec2(500, 300);
	ball->screen_bound = glm::vec2(Width, Height);
	ball->shader = ResourceManager::GetShader("sprite");
	ball->mesh = ResourceManager::GetMesh("sprite_quad");
	ball->textures["image"] = ResourceManager::GetTexture2D("ball");

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
		if (Keys[GLFW_KEY_SPACE] && ball->is_stuck)
		{
			ball->is_stuck = false;
			ball->velocity = glm::vec2(500, 300);
		}
		if (Keys[GLFW_KEY_A] && !Keys[GLFW_KEY_D])
		{
			player->velocity.x = -PLAYER_VELOCITY.x;
			if (ball->is_stuck)
			{
				if (ball->position.x >= player->size.x)
					ball->velocity.x = -PLAYER_VELOCITY.x;
				else
				{
					ball->velocity.x = 0;
					ball->position.x = player->size.x;
				}
			}
		}
		else if (!Keys[GLFW_KEY_A] && Keys[GLFW_KEY_D])
		{
			player->velocity.x = PLAYER_VELOCITY.x;
			if (ball->is_stuck)
			{
				if (ball->position.x <= Width - player->size.x)
					ball->velocity.x = PLAYER_VELOCITY.x;
				else
				{
					ball->velocity.x = 0;
					ball->position.x = Width - player->size.x;
				}
			}
		}
		else if (!Keys[GLFW_KEY_A] && !Keys[GLFW_KEY_D])
		{
			player->velocity.x = 0;
			if (ball->is_stuck)
			{
				ball->velocity.x = 0;
			}
		}
	}
}

// TODO : rename to check collisions
void Game::checkCollisions()
{
	if (!ball->is_alive)
	{
		reset();
	}
	//player->update(dt);
	//level->update(dt);
	// check collision
	for each (auto var in level->childrens)
	{
		if (!var->isDestroyed)
		{
			auto collision = ball->rigidBody.checkCollision(dynamic_cast<Brick*>(var)->rigidBody);
			if (std::get<0>(collision))
			{
				var->isDestroyed = true;
				int axis = static_cast<int>(std::get<1>(collision)) % 3;
				ball->velocity[axis] = -ball->velocity[axis];
				// reset position, rigid position will be update in scene.update
				ball->position += glm::vec2(std::get<2>(collision));
			}
		}
	}
	// check player and ball
	if (!ball->is_stuck)
	{
		auto collision = ball->rigidBody.checkCollision(player->rigidBody);
		if (std::get<0>(collision))
		{
			float distance = ball->position.x - player->position.x;
			float percentage = -distance / (player->size.x / 2.f);
			
			ball->velocity.x = 500 * percentage;
			ball->velocity.y = std::max(std::abs(ball->velocity.x) / 2, abs(ball->velocity.y));
			ball->velocity = glm::normalize(ball->velocity) * glm::length(PLAYER_VELOCITY);
		}
	}
}

void Game::render()
{
}

void Game::reset()
{
	resetPlayer();
	resetScene();
}

void Game::resetPlayer()
{
	// should be init at player init?
	player->size = glm::vec2(70, 15);
	player->position = glm::vec2(Width / 2.f, player->size.y);
	player->width = Width;
	player->shader = ResourceManager::GetShader("sprite");
	player->mesh = ResourceManager::GetMesh("sprite_quad");
	player->textures["image"] = ResourceManager::GetTexture2D("block");
	player->velocity = glm::vec2(0, 0);
	player->init();

	ball->size = glm::vec2(10, 10);
	ball->is_alive = true;
	ball->is_stuck = true;
	ball->position = player->position + glm::vec2(0, player->size.y + ball->size.y);
	ball->rigidBody.radius = 10.f;
	//ball->velocity = glm::vec2(500, 300);
	ball->screen_bound = glm::vec2(Width, Height);
	ball->shader = ResourceManager::GetShader("sprite");
	ball->mesh = ResourceManager::GetMesh("sprite_quad");
	ball->textures["image"] = ResourceManager::GetTexture2D("ball");
	ball->velocity = glm::vec2(0, 0);
	ball->init();
}

void Game::resetScene()
{
	size_t level_width = Width;
	size_t level_height = Height / 2;
	level->loadLevel("../level/level1.txt", level_width, level_height);
	level->position = glm::vec2(0.f, Height - level_height);
	for (auto c : level->childrens)
	{
		c->isDestroyed = false;
	}
}
