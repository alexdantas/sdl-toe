#include "Animation.hpp"

Animation::Animation(std::string filepath, int width, int height, int ammount)
{
    this->filepath   = filepath;
    this->frameWidth = width;
    this->frameHeight = height;
    this->maxFrame   = ammount;
    this->curFrame   = 0;
    this->sprite     = NULL;
	this->frames     = NULL;
    
    this->load();
}
Animation::~Animation()
{
	if (this->sprite) delete this->sprite;
    if (this->frames) delete this->frames;    
}
bool Animation::load()
{
	if (this->sprite) delete this->sprite;
    if (this->frames) delete this->frames;
    
	this->sprite = new Sprite(this->filepath);
    this->frames = new SDL_Rect [this->maxFrame];

    this->sprite->load();
    
	for (int i = 0; i < this->maxFrame; i++)
    {
        this->frames[i].x = i * this->frameWidth;
        this->frames[i].y = 0;
        this->frames[i].w = this->frameWidth;
        this->frames[i].h = this->frameHeight;           
    }
    
    return true;
}
void Animation::nextFrame()
{
    this->curFrame++;
    
    if (this->curFrame > this->maxFrame) this->restart();
}
void Animation::prevFrame()
{
    this->curFrame--;
    
    if (this->curFrame < 0) this->goToLast();
}
void Animation::restart()
{
    this->curFrame = 0;
}
void Animation::goToLast()
{
    this->curFrame = this->maxFrame;
}
void Animation::render(int x, int y)
{
    if (!this->sprite) return;

    SDL_Rect* curCrop = &(this->frames[curFrame]);
    this->sprite->crop(curCrop->x, curCrop->y, curCrop->w, curCrop->h);
    
    this->sprite->render(x, y);
}
void Animation::setTransparentRGBColor(int red, int green, int blue)
{
	this->sprite->setTransparentRGBColor(red, green, blue);
}
