#include "Game.h"



Game::Game(size_t width, size_t height)
	: Width(width), Height(height)
{
}


Game::~Game()
{
}

void Game::init()
{
	State = GAME_MENU;
}

void Game::render()
{
}
