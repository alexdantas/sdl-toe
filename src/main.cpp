
#include "SDLManager.hpp"
#include "Player.hpp"
#include "Font.hpp"

#define FONT_TTF_PATH "ttf/Terminus.ttf"

int main(int argc, char* argv[])
{
	global_sdl_manager = new SDLManager();
	if (global_sdl_manager->init(500, 500))
	{
		delete global_sdl_manager;
		return -1;
	}

	Player player(250, 12);
	player.show();

	Font font(FONT_TTF_PATH, 20);
	font.print(100, 300, "Hello, World 2!");
	font.print(5, 0, "Haha, outro teste!");
	font.print(200, 100, "Olha, o mario ali em cima!");

	global_sdl_manager->refreshScreen();
	global_sdl_manager->run();

	delete global_sdl_manager;
	return 0;
}

