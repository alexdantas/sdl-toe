/// @file Animation.hpp Deals with an animation onscreen.
//
//	This class uses a Sprite to show an animation.
//	Basically, it opens a large image and displays small pieces
//	of it on a configurable speed to simulate movement.
//
//	Keep in mind that it's your responsability to call the functions
//	at a nice rate.
//	Also, you should refresh the screen regularly to see any changes.
//
//	Basically, you should do this:
//	  Animation animation("path/to/image.png", width, height,  numberOfFrames, speed);
//		// on a loop...
//		animation.animate();
//		animation.render(x, y);
//
// This will create and animation and keep refreshing it. Don't worry,
// when it gets on the last frame, it'll restart flawlessly.

#ifndef ANIMATION_H_DEFINED
#define ANIMATION_H_DEFINED

#include "SDLManager.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

/// Deals with an animation based on a spritesheet
class Animation
{
public:
	/// Starts an animation based on #filepath, with #ammount sprites with
	/// #width each.
	//  @note If #speed is zero, will not animate at all (useful for a
	//        standing animation, for example).
	Animation(std::string filepath, int width, int height, int ammount, int speed=0);

	virtual ~Animation();

	/// Places the current sprite onscreen.
	//	Screen needs to be refreshed, though.
	void render(int x=0, int y=0);

	/// Animate by one step, based on the current animation speed.
	//	Must be called every once in a while to refresh the current sprite.
	void animate();

	/// Sets a RGB color on all sprites of this animation as transparent.
	//	This means when printing this image, this color will be
	//	passed-through and look invisible.
	void setTransparentRGBColor(int red=255, int green=0, int blue=255);

	/// Actually loads into memory all the stuff.
	//	@note Don't call this unless you want to reload the image -
	//	      it's already taken care of.
	bool load();

	/// Makes animation go to next frame.
	//	If it ever gets to the last, will restart.
	void nextFrame();

	/// Makes animation go to previous frame.
	//	If it ever gets to the first frame, will restart backwards.
	void prevFrame();

	/// Makes animation restart to first frame.
	void restart();

	/// Makes animation go to the last frame.
	void goToLast();

	/// Makes animation go to #frame.
	//	If it's not on the acceptable range, it does nothing.
	//	@note Frame counts start at zero!
	void goTo(int frame);

	/// Sets the current speed of animation to #speed.
	void setSpeed(int speed);

	/// Starts the animation, making all necessary preparations.
	//	Innefective if already started.
	void start();

	/// Stops the animation
	//	Innefective if already stopped.
	void stop();

	/// Tells if the animation has already started.
	bool isRunning();

private:
	unsigned int speed;
	unsigned int   frameWidth;
	unsigned int   frameHeight;
	bool  running;
	int	  curFrame;
	int	  maxFrame;
	Timer timer;
	std::string filepath;
	Sprite*		sprite;
	SDL_Rect*	frames;
};

#endif /* ANIMATION_H_DEFINED */
