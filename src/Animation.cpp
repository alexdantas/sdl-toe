#include "Animation.hpp"

Animation::Animation(std::string filepath, int width, int height, int ammount, int speed)
{
	this->filepath	  = filepath;
	this->frameWidth  = width;
	this->frameHeight = height;
	this->maxFrame	  = ammount;
	this->curFrame	  = 0;
	this->sprite	  = NULL;
	this->frames	  = NULL;
	this->speed		  = speed;
	this->running	  = false;
	this->load();
}
Animation::~Animation()
{
	if (this->sprite) delete   this->sprite;
	if (this->frames) delete[] this->frames;
}
bool Animation::load()
{
	if (this->sprite) delete   this->sprite;
	if (this->frames) delete[] this->frames;

	this->sprite = new Sprite(this->filepath);
	this->frames = new SDL_Rect [this->maxFrame];

	this->sprite->load();

	for (int i = 0; i < (this->maxFrame); i++)
	{
		this->frames[i].x = i * this->frameWidth;
		this->frames[i].y = 0;
		this->frames[i].w = this->frameWidth;
		this->frames[i].h = this->frameHeight;
	}
	return true;
}
void Animation::start()
{
	if (this->speed == 0)  return;
	if (this->isRunning()) return;

	this->running = true;
	this->timer.start();
}
void Animation::stop()
{
	if (this->speed == 0)   return;
	if (!this->isRunning()) return;

	this->running = false;
	this->timer.stop();
}
bool Animation::isRunning()
{
	return this->running;
}
void Animation::animate()
{
	if (this->speed == 0)   return;
	if (!this->isRunning()) return;

	this->timer.pause();
	if ((this->timer.delta()) < (this->speed))
    {
        timer.unpause();
		return;
    }

	this->nextFrame();
	this->timer.restart();
}
void Animation::nextFrame()
{
	if (this->speed == 0) return;

	this->curFrame++;

	if (this->curFrame >= this->maxFrame) this->restart();
}
void Animation::prevFrame()
{
	if (this->speed == 0) return;

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
void Animation::goTo(int frame)
{
	if ((frame >= 0) && (frame <= this->maxFrame))
		this->curFrame = frame;
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
void Animation::setSpeed(int speed)
{
	this->speed = speed;
}

