#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialiaze();
	if (success)
	{
		game.RunLoop();
	}

	game.Shutdown();
	return 0;
}