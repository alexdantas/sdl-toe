#include "Timer.hpp"

Timer::Timer()
{
	this->startMark = 0;
    this->stopMark  = 0;
    this->running   = false;
}
void Timer::start()
{
    this->startMark = SDL_GetTicks();
    this->running   = true;
}
void Timer::stop()
{
	this->stopMark = SDL_GetTicks();
    this->running  = false;
}
bool Timer::isRunning()
{
    return this->running;
}
Uint32 Timer::delta_ms()
{
    if (this->isRunning())
        return this->currentTime();

    // Hasn't started yet
	if (this->stopMark == 0)
        return 0;

	return this->stopMark - this->startMark;
}
Uint32 Timer::currentTime()
{
	return SDL_GetTicks() - this->startMark;
}
