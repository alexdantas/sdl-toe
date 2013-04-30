#include "VisibleObject.hpp"

VisibleObject::VisibleObject(float x, float y)
{
	this->x = x;
	this->y = y;
	this->animation = NULL;
}
VisibleObject::~VisibleObject()
{
	if (this->animation) delete[] this->animation;
}
void VisibleObject::setPosition(float x=0, float y=0)
{
	this->x = x;
	this->y = y;
}
void VisibleObject::moveDown(float x)
{
	this->y -= x;
}
void VisibleObject::moveUp(float x)
{
	this->y += x;
}
void VisibleObject::moveLeft(float x)
{
	this->x -= x;
}
void VisibleObject::moveRight(float x)
{
	this->x += x;
}

