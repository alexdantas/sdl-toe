// main.cpp
// Starting point of execution
#include "SDLManager.hpp"
#include "GameManager.hpp"

int main(int argc, char* argv[])
{
	if (!SDLManager::init(320, 370, 30))
	{
		SDLManager::errorLog("Couldn't start SDL!");
		return -1;
	}
	GameManager game;

	// This is the main loop of the game.
	game.run();

	return 0;
}

