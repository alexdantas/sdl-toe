
#include "Font.hpp"

Font::Font(std::string filepath, int size)
{
	this->surface = NULL;
    this->font    = NULL;
    this->setFont(filepath, size);
	this->setColor(255, 255, 255);
	this->load();
}
Font::~Font()
{
//  Why does this gives me a Segmentation Fault?
//	if (this->font)    TTF_CloseFont(this->font);
	if (this->surface) SDL_FreeSurface(this->surface);
}
bool Font::load()
{
	if (this->font) TTF_CloseFont(this->font);
    
	this->font = TTF_OpenFont(this->filepath.c_str(), this->size);
	if (!this->font)
		return false;

	return true;
}
void Font::setFont(std::string filepath, int size)
{
	this->filepath = filepath;
	this->size = size;
}
void Font::setColor(int red, int green, int blue)
{
	this->color.r = red;
	this->color.g = green;
	this->color.b = blue;        
}
bool Font::print(int x, int y, std::string text)
{
	if (this->surface) SDL_FreeSurface(this->surface);

	this->surface = TTF_RenderText_Solid(this->font, text.c_str(), this->color);
	if (!this->surface)
		return false;

	// tells where to render
	SDL_Rect tmpRect;
	tmpRect.x = x;
	tmpRect.y = y;
    
	global_sdl_manager->renderSurface(this->surface, NULL, &tmpRect);    
	return true;
}
bool Font::print(int x, int y, std::string text, std::string style)
{
    int cur_style = TTF_STYLE_NORMAL;

	if (style == "bold")
        cur_style = TTF_STYLE_BOLD;
    
    else if (style == "italic")
        cur_style = TTF_STYLE_ITALIC;

    else if (style == "underline")
        cur_style = TTF_STYLE_UNDERLINE;

    // we can use | to set several styles
    // maybe i should create a nicer interface to it
    TTF_SetFontStyle(this->font, cur_style);
    return this->print(x, y, text);
}
int Font::getW()
{
    if (this->surface)	return this->surface->w;
    return 0;
}
int Font::getH()
{
	if (this->surface) return this->surface->h;
    return 0;
}
// I made these based on this tutorial:
// http://www.sdltutorials.com/sdl-ttf
// but it doesn't seem to be working, DAMN
// 
// void Font::setOutline(int size)
// {
// 	TTF_SetFontOutline(this->font, size);
// }
// int  Font::getOutline()
// {
//     TTF_GetFontOutline(this->font);
// }
// void Font::resetOutline()
// {
//     this->setOutline(0);
// }

