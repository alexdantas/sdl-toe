
#include "SDLManager.hpp"
#include "Font.hpp"

// Declaration of the global sdl manager
SDLManager* global_sdl_manager = NULL;

SDLManager::SDLManager()
{
	this->screen = NULL;
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
void SDLManager::run()
{    
	//while(!SDL_QuitRequested());

	bool quit = false;
	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
		        inputText(event.key.keysym.sym);
            
			if (event.type == SDL_QUIT)
				quit = true;
		}
        this->refreshScreen();
	}
}
void SDLManager::inputText(SDLKey key)
{
    static Font font("ttf/Terminus.ttf", 24);
    
	static std::string text = "";
	if (key == SDLK_BACKSPACE)
    {
		if (!text.empty())
            text.erase(text.length() - 1);
	}
	else if (key == SDLK_RETURN)
    {
		text = "";
	}
	else
    {
		if (text.length() < 20)
        {
			if (key == ' ' || key >= 'a' || key <= 'z' ||
                key >= 'A' || key <= 'Z' || key >= '0' ||
                key <= '9')
                text += key;
		}
	}
    font.print(50, 50, text);
}

