#ifndef SDLMANAGER_H_DEFINED
#define SDLMANAGER_H_DEFINED

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

//* Handles all direct SDL calls
//  A simple SDL object wrapper
class SDLManager
{
public:
    SDLManager();
    virtual ~SDLManager();

	/// Starts all things related to SDL.
	//  The constructor only allocates stuff, here's where the
	//  action begins.
	//  @return true if OK, false if something's wrong
	//  @note   I encourage you to call `delete` if this returns -1.
	bool init(int width, int height);

	/// Pauses the whole program for #delay milliseconds (1/1000 of a second).
	void delay_ms(int delay);

	/// Loads image specified by #filename.
	//  @return The pointer to it if OK, NULL if something strange happened.
	//  @note   Remember to call freeImage() if loaded sucessfully.
	SDL_Surface* loadImage(std::string filename);

	/// Cleans #image from memory, safe-checking if NULL.
	void freeImage(SDL_Surface* image);

	/// Effectively draws everything that's onscreen.
	//  @note Need to be called constantly.
	void refreshScreen();

	/// Places the surface #source (on #position and #cropped) onscreen.
	//  @note Need to call refreshScreen() after.
	void renderSurface(SDL_Surface* source, SDL_Rect* crop, SDL_Rect* position);

	void run();

    void inputText(SDLKey key);
    
private:
	/// Represents the whole game screen.
	SDL_Surface* screen;
};

//* Singleton global SDL Manager
//  Pretty much everyone depends on this
//  @note Must be initialized with init()
extern SDLManager* global_sdl_manager;

#endif /* SDLMANAGER_H_DEFINED */

