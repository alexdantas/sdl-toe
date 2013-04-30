#ifndef VISIBLEOBJECT_H_DEFINED
#define VISIBLEOBJECT_H_DEFINED

#include "Animation.hpp"

class VisibleObject
{
public:
	VisibleObject(float x=0, float y=0);
	virtual ~VisibleObject();

	/// Sets the current position to #x and #y.
	void setPosition(float x, float y);

	void moveDown(float x);
	void moveUp(float x);
	void moveLeft(float x);
	void moveRight(float x);

protected:
	float x;
	float y;
	Animation* animation;
};

#endif /* VISIBLEOBJECT_H_DEFINED */
