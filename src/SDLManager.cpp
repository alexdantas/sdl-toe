
#include <sstream> // for autocasting values into strings
#include "SDLManager.hpp"

// Must intialize static members out of the class D:
SDL_Surface* SDLManager::screen          = NULL;
bool         SDLManager::willQuit        = false;
int          SDLManager::screenW         = 0;
int          SDLManager::screenH         = 0;
uint32_t     SDLManager::framerate       = 0;
uint32_t     SDLManager::framerate_delay = 0;
uint32_t     SDLManager::frame_delta     = 0;
Timer        SDLManager::framerate_timer;

SDLManager::SDLManager()
{
    // All values are already initialized up there
}
SDLManager::~SDLManager()
{
	//Mix_Quit();
	Mix_CloseAudio();
	SDL_EnableUNICODE(SDL_DISABLE);
	TTF_Quit();

	// SDL_Quit already does this for me
	//SDL_FreeSurface(screen);

	SDL_Quit();
}
bool SDLManager::init(int width, int height, int framerate)
{
	int retval = 0;

	// SDL
	retval = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (retval)
	{
		SDLManager::errorLog("Couldn't start SDL");
		return false;
	}

	// Video
	screenW = width;
	screenH = height;
	screen	= SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	if (!screen)
	{
		SDLManager::errorLog("Couldn't set video mode");
		return false;
	}

	// TTF
	if (TTF_Init())
	{
		SDLManager::errorLog("Couldn't start TTF");
		return false;
	}
	SDL_EnableUNICODE(SDL_ENABLE);

	// TODO: how do I find out the optimal audio rate of a music?
	int	   audio_rate	  = 30000;	   // Default is 22050
	Uint16 audio_format	  = AUDIO_S16; // 16-bit stereo
	int	   audio_channels = 2;
	int	   audio_buffers  = 4096;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		SDLManager::errorLog("Mix_OpenAudio: Couldn't start Audio");
		return false;
	}

	// I saw this here: http://www.kekkai.org/roger/sdl/mixer/
	// but don't quite know what it does.
	//Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	// Framerate manager
	framerate = framerate;
	framerate_delay = (1000/framerate); // 1 second

	SDL_WM_SetCaption("Platformer", "hey, get back here!");

	framerate_timer.start();
	return true;
}
void SDLManager::framerateWait()
{
	frame_delta = framerate_timer.delta();

	if ((frame_delta) < (framerate_delay))
		SDLManager::delay_ms((framerate_delay) - frame_delta);

	framerate_timer.restart();
}
Uint32 SDLManager::getFramerateDelay()
{
	return framerate_delay;
}
void SDLManager::delay_ms(int delay)
{
	SDL_Delay(delay);
}
uint32_t SDLManager::getDelta()
{
    return frame_delta;
}
SDL_Surface* SDLManager::loadImage(std::string filename)
{
	SDL_Surface* tmpImage = NULL;
	tmpImage = IMG_Load(filename.c_str());

	// Optimizing image to screen, while trying to mantain it's
	// transparency (alpha)
	SDL_Surface* image = NULL;
	if (tmpImage->format->Amask)
		image = SDL_DisplayFormatAlpha(tmpImage);
	else
		image = SDL_DisplayFormat(tmpImage);

	SDLManager::freeImage(tmpImage);
	return image;
}
void SDLManager::freeImage(SDL_Surface* image)
{
	if (image) SDL_FreeSurface(image);
}
void SDLManager::renderSurface(SDL_Surface* source, SDL_Rect* crop=NULL, SDL_Rect* position=NULL)
{
	SDL_BlitSurface(source, crop, screen, position);
}
void SDLManager::refreshScreen()
{
	SDL_Flip(screen);
}
void SDLManager::clearScreen()
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
}
bool SDLManager::isPrintable(SDLKey key)
{
	if (key == ' ' ||
		key >= 'a' || key <= 'z' ||
		key >= 'A' || key <= 'Z' ||
		key >= '0' || key <= '9')
		return true;
	else
		return false;
}
void SDLManager::errorLog(std::string msg)
{
	std::cerr << msg << std::endl;
}
bool SDLManager::musicPlaying()
{
	if (Mix_PlayingMusic())
		return true;
	else
		return false;
}
bool SDLManager::musicPaused()
{
	if (Mix_PausedMusic())
		return true;
	else
		return false;
}
void SDLManager::pauseMusic()
{
	if (SDLManager::musicPlaying())
		Mix_PauseMusic();
}
void SDLManager::resumeMusic()
{
	if (SDLManager::musicPaused())
		Mix_ResumeMusic();
}
void SDLManager::stopMusic()
{
	if (SDLManager::musicPlaying() || SDLManager::musicPaused())
		Mix_HaltMusic();
}
