
#include "Sprite.hpp"

Sprite::Sprite(std::string filename)
{
	setFilename(filename);
	this->surface  = NULL;
    this->load();
}
Sprite::~Sprite()
{
	if (this->surface) SDL_FreeSurface(this->surface);
}
void Sprite::setFilename(std::string newFilename)
{
	this->filename = newFilename;
}
bool Sprite::load()
{
	if (this->surface) SDL_FreeSurface(this->surface);
    
	this->surface = SDLManager::loadImage(this->filename);
    if (!this->surface)
    {
        SDLManager::errorLog("Couldn't load sprite on " + this->filename);
        return false;
    }

	// Will print image at it's original size
	this->crop(0, 0, this->surface->w, this->surface->h);
    return true;
}
void Sprite::crop(int x, int y, int w, int h)
{
	this->clipRect.x = x;
	this->clipRect.y = y;
	this->clipRect.w = w;
	this->clipRect.h = h;
}
void Sprite::render(int x, int y)
{
	// tells where to render
	SDL_Rect tmpRect;
	tmpRect.x = x;
	tmpRect.y = y;

	global_sdl_manager->renderSurface(this->surface, &(this->clipRect), &tmpRect);
}
void Sprite::setTransparentRGBColor(int red, int green, int blue)
{
	Uint32 colorKey = SDL_MapRGB(this->surface->format, red, green, blue);

	SDL_SetColorKey(this->surface, SDL_SRCCOLORKEY, colorKey);
}

