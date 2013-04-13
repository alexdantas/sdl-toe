
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
    SDL_EnableUNICODE(SDL_DISABLE);
	// SDL_Quit already does this for me
	//SDL_FreeSurface(this->screen);
	SDL_Quit();
	TTF_Quit();
}
bool SDLManager::init(int width, int height)
{
	int retval = 0;

	retval = SDL_Init(SDL_INIT_EVERYTHING);
	if (retval)
		return false;

    this->screenW = width;
    this->screenH = height;
	this->screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
	if (!this->screen)
		return false;

	if (TTF_Init())
		return false;

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

	freeImage(tmpImage);
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
		        inputText(event.key.keysym.sym, event.key.keysym.unicode);
            
			if (event.type == SDL_QUIT)
				this->willQuit = true;
		}
        this->refreshScreen();
	}
}
void SDLManager::inputText(SDLKey key, Uint16 unicode)
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
    font.print((this->screenW - buffer.getLength())/2,
               (this->screenH)/2, buffer.get().c_str());
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

