
#include "SDLManager.hpp"
#include "Font.hpp"
#include "Buffer.hpp"

// Declaration of the global sdl manager
SDLManager* global_sdl_manager = NULL;

SDLManager::SDLManager()
{
	this->screen   = NULL;
    this->willQuit = false;
}
SDLManager::~SDLManager()
{
    Mix_CloseAudio();
    SDL_EnableUNICODE(SDL_DISABLE);
	TTF_Quit();    
	// SDL_Quit already does this for me
	//SDL_FreeSurface(this->screen);
	SDL_Quit();
}
bool SDLManager::init(int width, int height)
{
	int retval = 0;

	retval = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (retval)
    {
        SDLManager::errorLog("Couldn't start SDL");
		return false;
    }

    this->screenW = width;
    this->screenH = height;
	this->screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	if (!this->screen)
    {
        SDLManager::errorLog("Couldn't set video mode");
		return false;
    }

	if (TTF_Init())
    {
        SDLManager::errorLog("Couldn't start TTF");        
		return false;
    }

    // TODO: how do I find out the optimal audio rate of a music?
    int    audio_rate     = 30000;  //44000; //22050;
    Uint16 audio_format   = AUDIO_S16; // 16-bit stereo
    int    audio_channels = 2;
    int    audio_buffers  = 4096;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
    {
        SDLManager::errorLog("Couldn't start Audio");        
        return false;
    }

    // I say this here: http://www.kekkai.org/roger/sdl/mixer/
    // but don't quite know what it does.
    //Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
    
    
	SDL_WM_SetCaption("Platformer", "hey, get back here!");
	SDL_EnableUNICODE(SDL_ENABLE);
	return 0;
}
void SDLManager::delay_ms(int delay)
{
	SDL_Delay(delay);
}
SDL_Surface* SDLManager::loadImage(std::string filename)
{
	SDL_Surface* tmpImage = NULL;
	tmpImage = IMG_Load(filename.c_str());

	// optimizing image to screen, while trying to mantain
	// it's transparency (alpha)
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
    SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));}    
void SDLManager::run()
{    
	//while(!SDL_QuitRequested());
	SDL_Event event;

	while (!this->willQuit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
            {
		        bufferInput(event.key.keysym.sym, event.key.keysym.unicode);
            }
            
			if (event.type == SDL_QUIT)
				this->willQuit = true;
		}
        this->refreshScreen();
		this->delay_ms(50);
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
