
#include <sstream> // for autocasting values into strings
#include "SDLManager.hpp"

// Must intialize static members out of the class D:
SDL_Surface* SDLManager::screen          = NULL;
SDL_Surface* SDLManager::bg              = NULL;
SDL_Surface* SDLManager::x               = NULL;
SDL_Surface* SDLManager::o               = NULL;
int          SDLManager::screenW         = 0;
int          SDLManager::screenH         = 0;
uint32_t     SDLManager::framerate       = 0;
uint32_t     SDLManager::framerate_delay = 0;
uint32_t     SDLManager::frame_delta     = 0;
Timer        SDLManager::framerate_timer;
bool         SDLManager::startedAudio        = true;

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
	freeImage(bg);
    freeImage(x);
    freeImage(o);

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
	int	   audio_rate	  = 22050;	   // Default is 22050
	Uint16 audio_format	  = AUDIO_S16; // 16-bit stereo
	int	   audio_channels = 2;
	int	   audio_buffers  = 4096;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
		SDLManager::warningLog("Mix_OpenAudio: Couldn't start Audio");
        startedAudio = false;
    }

	// I saw this here: http://www.kekkai.org/roger/sdl/mixer/
	// but don't quite know what it does.
	//Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	// Framerate manager
	framerate = framerate;
	framerate_delay = (1000/framerate); // 1 second

	SDL_WM_SetCaption("SDL-toe", "hey, get back here!");

    bg = SDLManager::loadImage("img/bg.png");
    x  = SDLManager::loadImage("img/x.png");
    o  = SDLManager::loadImage("img/o.png");
	if (!bg || !x || !o)
        return false;

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
void SDLManager::renderBackground()
{
	SDL_Rect tmpRect;
	tmpRect.x = 0;
	tmpRect.y = 0;

	SDLManager::renderSurface(bg, NULL, &tmpRect);
}
void SDLManager::renderX(int i, int j)
{
	SDL_Rect tmpRect;
	tmpRect.x = i*100 + i*10;
	tmpRect.y = j*100 + j*10;

	SDLManager::renderSurface(x, NULL, &tmpRect);
}
void SDLManager::renderO(int i, int j)
{
	SDL_Rect tmpRect;
	tmpRect.x = i*100 + i*10;
	tmpRect.y = j*100 + j*10;

	SDLManager::renderSurface(o, NULL, &tmpRect);
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
	std::cerr << "Error: " << msg << std::endl;
}
void SDLManager::warningLog(std::string msg)
{
	std::cerr << "Warning: " << msg << std::endl;
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
bool SDLManager::isInsideGrid(int x, int y)
{
    if (x >= 0 && x <= 320)
        if (y >= 0 && y<= 320)
            return true;

    return false;
}
bool SDLManager::isValidCell(int x, int y)
{
    int cellW = 100;
    int cellH = 100;
    int lineW = 10;
    int lineH = 10;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
			if (x >= (i*cellW + i*lineW) && x <= (cellW + i*cellW + i*lineW))
	        	if (y>= (j*cellH + j*lineH) && y <= (cellH + j*cellH + j*lineH))
	                return true;

    return false;
}
int SDLManager::getIndexX(int x)
{
    int cellW = 100;
    int lineW = 10;

    for (int i = 0; i < 3; i++)
        if (x >= (i*cellW + i*lineW) && x <= (cellW + i*cellW + i*lineW))
                return i;

    return 0;
}
int SDLManager::getIndexY(int y)
{
    int cellH = 100;
    int lineH = 10;

    for (int j = 0; j < 3; j++)
		if (y>= (j*cellH + j*lineH) && y <= (cellH + j*cellH + j*lineH))
			return j;

    return 0;
}
bool SDLManager::isInsideResetButton(int x, int y)
{
	return !isInsideGrid(x, y);
}
bool SDLManager::hasAudio()
{
    return startedAudio;
}

