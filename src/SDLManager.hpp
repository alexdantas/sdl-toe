#ifndef SDLMANAGER_H_DEFINED
#define SDLMANAGER_H_DEFINED

#include <string>
#include <iostream>
#include <stdint.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "Buffer.hpp"
#include "Timer.hpp"

#define GRAVITY 0.5

/// Handles all direct SDL calls
//	A simple SDL object wrapper
class SDLManager
{
public:
	SDLManager();
	virtual ~SDLManager();

	/// Starts all things related to SDL.
	//	The constructor only allocates stuff, here's where the
	//	action begins.
	//	@return true if OK, false if something's wrong
	//	@note	I encourage you to call `delete` if this returns -1.
	static bool init(int width, int height, int framerate=60);

	/// Effectively draws everything that's onscreen.
	//	@note Need to be called constantly.
	static void refreshScreen();

	/// Clears whole screen to black.
	static void clearScreen();

	/// Places the surface #source (on #position and #cropped) onscreen.
	//	@note Need to call refreshScreen() after.
	static void renderSurface(SDL_Surface* source, SDL_Rect* crop, SDL_Rect* position);

	/// Pauses the whole program for #delay milliseconds (1/1000 of a second).
	static void delay_ms(int delay);

	/// Loads image specified by #filename.
	//	@return The pointer to it if OK, NULL if something strange happened.
	//	@note	Remember to call freeImage() if loaded sucessfully.
	static SDL_Surface* loadImage(std::string filename);

	/// Cleans #image from memory, safe-checking if NULL.
	static void freeImage(SDL_Surface* image);

	/// Prints #msg on standard error output.
	//	Defaults to the console.
	static void errorLog(std::string msg);

	/// Tells if there's any music playing anywhere on the game.
	static bool musicPlaying();

	/// Tells if there's any paused music anywhere on the game.
	static bool musicPaused();

	/// Pauses any music that could be playing.
	//	It safe-checks so you don't have to.
	static void pauseMusic();

	/// Resumes any music that may be paused.
	//	It safe-checks so you don't have to.
	static void resumeMusic();

	/// Stops any music that may be playing or paused.
	//	It safe-checks so you don't have to.
	//	@note Any subsequent calls to pauseMusic() and resumeMusic()
	//		  will be ignored.
	static void stopMusic();

	/// Returns the ammount of time each frame should have according
	//	to the framerate.
	static Uint32 getFramerateDelay();

	/// Waits as long as needed to keep the framerate, if necessary.
	//	@note Sometimes it will not sleep at all.
	static void framerateWait();

	/// Returns the ammount of time the last frame had.
	static uint32_t getDelta();

	/// Tells if the #key can be printed onscreen (not a control key).
	//	If a key is visible according to the ASCII table.
	static bool isPrintable(SDLKey key);

private:
	/// Represents the whole game screen.
	static SDL_Surface* screen;

	static int screenW;
	static int screenH;

static bool willQuit;
	/// The framerate. By default, 60 frames per second.
	static uint32_t framerate;

	/// How much time each frame must have according to the framerate.
	static uint32_t framerate_delay;

	/// The timer that keeps calculating the delta between frames.
	static Timer  framerate_timer;

	static uint32_t frame_delta;
};

#endif /* SDLMANAGER_H_DEFINED */
