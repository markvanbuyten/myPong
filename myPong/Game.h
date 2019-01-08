#pragma once

#include "F:\SDL\include\SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();

	bool Initialiaze();

	void RunLoop();

	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;

	bool mIsRunning;

	SDL_Renderer* mRenderer;

	Vector2 mPaddleRightPos, mPaddleLeftPos;
	Vector2 mBallPos;
	Vector2 mBallVelocity;

	Uint32 mTicksCount;

	int mPaddleLeftDirection, mPaddleRightDirection;
};
