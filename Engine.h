#pragma once

class GameMode;
class Engine
{
public:
	explicit Engine();
	~Engine();

	void LoadGameMode(GameMode* newGameMode);

	void Run();

	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

	void QuitGame();

private:
	GameMode* gameMode = nullptr;

	bool quit;

	int blockX;
	int blockY;
};

