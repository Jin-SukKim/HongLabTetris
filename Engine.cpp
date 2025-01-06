#include "Engine.h"
#include "GameMode.h"

#include <iostream>
#include <Windows.h>

Engine::Engine()
	: gameMode(nullptr),quit(false),blockX(0),blockY(0)
{
	LoadGameMode(new GameMode());
	blockX = gameMode->GetWidth() / 2;
	blockY = 0;
}

Engine::~Engine()
{
	if(gameMode != nullptr)
	{
		delete gameMode;
		gameMode = nullptr;
	}
}

void Engine::LoadGameMode(GameMode * newGameMode)
{
	gameMode = newGameMode;
}

void Engine::Run()
{
	gameMode->initializeBoard();

	// 고해상도 카운터
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	int64_t currentTime = 0;
	int64_t previousTime = counter.QuadPart;

	float targetFrameRate = 60.0f;
	float targetOneFrameTime = 1.0f / targetFrameRate;

	// Main Game Loop
	while(true)
	{
		if(quit)
		{
			break;
		}

		// 프레임 시간 계산
		QueryPerformanceCounter(&counter);
		currentTime = counter.QuadPart;

		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);

		if(deltaTime >= targetOneFrameTime)
		{
			ProcessInput();
			Update(deltaTime);
			Draw();

			previousTime = currentTime;
		}
	}
}

void Engine::ProcessInput()
{}

void Engine::Update(float deltaTime)
{
	// Move the block down
	blockY++;
	if(blockY >= gameMode->GetHeight())
	{
		blockY = 0; // Reset block position to the top
	}

	Sleep(500);
}

void Engine::Draw()
{
	gameMode->clearScreen();
	gameMode->drawBlock(blockX,blockY - 1,blockX,blockY);
	gameMode->drawBoard();
}

void Engine::QuitGame()
{
	quit = true;
}
