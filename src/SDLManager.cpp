
#include <sstream> // for autocasting values into strings
#include "SDLManager.hpp"
#include "Font.hpp"
#include "Buffer.hpp"
#include "Player.hpp"
#include "Music.hpp"
#include "Timer.hpp"

// Declaration of the global sdl manager
SDLManager* global_sdl_manager = NULL;

SDLManager::SDLManager()
{
	this->screen   = NULL;
    this->willQuit = false;
}
SDLManager::~SDLManager()
{
//    Mix_Quit();
    Mix_CloseAudio();
    SDL_EnableUNICODE(SDL_DISABLE);
	TTF_Quit();
	// SDL_Quit already does this for me
	//SDL_FreeSurface(this->screen);
	SDL_Quit();
}
bool SDLManager::init(int width, int height, int framerate)
{
	int retval = 0;

    // SDL
	retval = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (retval)
    {
        SDLManager::errorLog("Couldn't start SDL");
		return false;
    }

    // Video
    this->screenW = width;
    this->screenH = height;
	this->screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	if (!this->screen)
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

// Don't I need to do this to support MP3 and OGG?
// Why on earth does this always fails?
// Well... bitwise operators suck anyway...
//
//    int flags   = MIX_INIT_OGG | MIX_INIT_MP3;
//    int initted = Mix_Init(flags);
//    if ((initted&flags) != flags)
//    {
//        SDLManager::errorLog("Mix_Init: Couldn't start OGG and MP3 support");
//        return false;
//	}

    // TODO: how do I find out the optimal audio rate of a music?
    int    audio_rate     = 30000;     // Default is 22050
    Uint16 audio_format   = AUDIO_S16; // 16-bit stereo
	int    audio_channels = 2;
    int    audio_buffers  = 4096;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        SDLManager::errorLog("Mix_OpenAudio: Couldn't start Audio");
        return false;
    }

    // I saw this here: http://www.kekkai.org/roger/sdl/mixer/
    // but don't quite know what it does.
    //Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);

	// Framerate manager
	this->framerate = framerate;

	SDL_WM_SetCaption("Platformer", "hey, get back here!");
	return true;
}
void SDLManager::framerateWait()
{
	// this function's supposed to wait as long as needed
	// to keep a custom framerate
	// How will I implement it ?
}

void SDLManager::delay_ms(int delay)
{
	SDL_Delay(delay);
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
	SDL_BlitSurface(source, crop, this->screen, position);
}
void SDLManager::refreshScreen()
{
	SDL_Flip(this->screen);
}
void SDLManager::clearScreen()
{
    SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
}
void SDLManager::run()
{
	//while(!SDL_QuitRequested());
	SDL_Event event;

	Player player(250, 12);

	Font font("ttf/Terminus.ttf", 20);

    Music music("ogg/mmx-intro.ogg");
    music.play();

	Timer timer;
    timer.start();

// 60 frames per second
#define MIN_FRAMETIME_MSECS (1000/60)

	while (!this->willQuit)
	{
	    // Let's wait a second if the framerate is too low.
	    timer.stop();
    	Uint32 delta = timer.delta_ms();

        // comment this to unlimit the framerate
        if (delta < MIN_FRAMETIME_MSECS)
		    SDL_Delay(MIN_FRAMETIME_MSECS - delta);
//		this->framerateWait();

		timer.start();

		static std::stringstream showDelta;
        showDelta.str("");
		showDelta << "Delta: " <<  delta << " ms";
	   	font.print(0, 400, showDelta.str().c_str());

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
            {
		        bufferInput(event.key.keysym.sym, event.key.keysym.unicode);
                switch (event.key.keysym.sym)
                {
                case SDLK_p:
                    SDLManager::pauseMusic();
                    break;
                case SDLK_r:
                    SDLManager::resumeMusic();
                    break;
                case SDLK_s:
                    SDLManager::stopMusic();
                    break;
				case SDLK_n:
//					player.nextAnimation();
                    break;
                default: break;
                }
            }

			if (event.type == SDL_QUIT)
				this->willQuit = true;
		}

        this->clearScreen();
        font.print(0, 10, "Teste de SDL");
        font.print(0, 30, "p: pausa musica");
        font.print(0, 50, "r: continua musica");
        font.print(0, 70, "s: para musica");
        font.print(0, 90, "ESC: sai do \"jogo\"");
        font.print(200, 100, "Digite alguma coisa para mim");

		player.show();

        this->refreshScreen();
//		this->delay_ms(250);
	}
}
void SDLManager::bufferInput(SDLKey key, Uint16 unicode)
{
    static Font font("ttf/Terminus.ttf", 24);
    static Buffer buffer;

	if (key == SDLK_BACKSPACE)
		buffer.backspace();

	else if (key == SDLK_RETURN)
		buffer.clear();

    else if (key == SDLK_ESCAPE)
        this->willQuit = true;

	else
    {
        if (isPrintable(key))
        {
            char c = unicode;
            buffer.addChar(c);
        }
    }
    font.print(0, (this->screenH)/2, buffer.get().c_str());
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
