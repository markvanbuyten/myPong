#include "Game.h"

const int thickness = 15;
const float pHeight = 100.0f;

Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mIsRunning = true;
	mTicksCount = 0;
	mPaddleLeftDirection = 0;
	mPaddleRightDirection = 0;
}

bool Game::Initialiaze()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"my PONG-game",
		100,	//Top left x-coordinate of window
		100,	//Top left y-coordinate of window
		1024,	//Width of window
		768,	//Height of window
		0		//Flag (0 for no flags)
		);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false();
	}

	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mPaddleLeftPos.x = 10.0f;
	mPaddleLeftPos.y = 768.0f / 2.0f;
	mPaddleRightPos.x = 999.0f;
	mPaddleRightPos.y = 768.0f / 2.0f;

	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleLeftDirection = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleLeftDirection -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleLeftDirection += 1;
	}

	mPaddleRightDirection = 0;
	if (state[SDL_SCANCODE_O])
	{
		mPaddleRightDirection -= 1;
	}
	if (state[SDL_SCANCODE_L])
	{
		mPaddleRightDirection += 1;
	}
}

void Game::UpdateGame()
{
	//Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	//Delta time is the difference int ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	mTicksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	if (mPaddleLeftDirection != 0)
	{
		mPaddleLeftPos.y += mPaddleLeftDirection * 300.0f * deltaTime;

		if (mPaddleLeftPos.y < (pHeight / 2.0f + thickness))
		{
			mPaddleLeftPos.y = pHeight / 2.0f + thickness;
		}
		else if (mPaddleLeftPos.y > (768.0f - pHeight - thickness))
		{
			mPaddleLeftPos.y = 768.0f - pHeight - thickness;
		}
	}

	if (mPaddleRightDirection != 0)
	{
		mPaddleRightPos.y += mPaddleRightDirection * 300.0f * deltaTime;

		if (mPaddleRightPos.y < (pHeight / 2.0f + thickness))
		{
			mPaddleRightPos.y = pHeight / 2.0f + thickness;
		}
		else if (mPaddleRightPos.y > (768.0f - pHeight - thickness))
		{
			mPaddleRightPos.y = 768.0f - pHeight - thickness;
		}
	}
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRenderer,
		0,
		0,
		255,
		255
	);

	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(
		mRenderer, 
		0, 
		0, 
		0, 
		255
	);
	
	//drawing top wall
	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &wall);
	
	//drawing bottom wall
	wall.y = 768 - thickness;

	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};

	SDL_RenderFillRect(mRenderer, &ball);

	SDL_Rect paddleLeft{
		static_cast<int>(mPaddleLeftPos.x),
		static_cast<int>(mPaddleLeftPos.y -pHeight/2),
		thickness,
		static_cast<int>(pHeight)
	};

	SDL_RenderFillRect(mRenderer, &paddleLeft);

	SDL_Rect paddleRight{
		static_cast<int>(mPaddleRightPos.x),
		static_cast<int>(mPaddleRightPos.y - pHeight/2),
		thickness,
		static_cast<int>(pHeight)
	};

	SDL_RenderFillRect(mRenderer, &paddleRight);

	SDL_RenderPresent(mRenderer);
}