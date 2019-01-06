#pragma once

#include "F:\SDL\include\SDL.h"

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
};
