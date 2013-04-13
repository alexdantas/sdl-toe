
#include "SDLManager.hpp"
#include "Font.hpp"
#include "Music.hpp"

#define FONT_TTF_PATH "ttf/Terminus.ttf"

int main(int argc, char* argv[])
{
	global_sdl_manager = new SDLManager();
	if (global_sdl_manager->init(500, 500))
	{
		delete global_sdl_manager;
		return -1;
	}

	Font font(FONT_TTF_PATH, 20);
	font.print(200, 100, "Olha, o mario ali em cima!");

    Music music("ogg/mmx-intro.ogg");
    music.play();
    
	global_sdl_manager->refreshScreen();
	global_sdl_manager->run();

	delete global_sdl_manager;
	return 0;
}

