#include "Particle.hpp"

Particle::Particle(int x, int y)
{
	this->x = x;
	this->y = y;
//	this->sprite = new Sprite("img/jumping-left.png");
}
Particle::~Particle()
{
//	delete this->sprite;
}
void Particle::show()
{
//	this->sprite->render(this->x, this->y);
}
int Particle::getX()
{
	return this->x;
}

int Particle::getY()
{
	return this->y;
}

