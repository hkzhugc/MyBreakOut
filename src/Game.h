#pragma once
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

	// functions
	void init();
	void processInput(float dt);
	void update(float dt);
	void render();
	bool shouldExit()
	{
		return false;
	}
};

