
#include "SDLManager.hpp"

int main(int argc, char* argv[])
{
	// shut up, damn compiler
	if (argc == 666)
        return (int)argv[1337];

	global_sdl_manager = new SDLManager();
	if (!global_sdl_manager->init(500, 500))
	{
		delete global_sdl_manager;
		return -1;
	}

	global_sdl_manager->refreshScreen();
	global_sdl_manager->run();

	delete global_sdl_manager;
	return 0;
}
