#pragma once
#include "Player.h"
#include "GameLevel.h"
#include "Ball.h"
class Game
{
public:
	enum GameState {
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};
	Game(size_t width, size_t height);
	~Game();

	// members
	GameState State;
	bool      Keys[1024];
	size_t Width, Height;
	Ball*   ball;
	Player* player;
	GameLevel* level;

	// functions
	void init();
	void processInput();
	void checkCollisions();
	void render();
	bool shouldExit()
	{
		return false;
	}
private:
	void reset();
	void resetPlayer();
	void resetScene();
};

