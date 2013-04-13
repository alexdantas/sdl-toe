/// @file Animation.hpp Deals with an animation onscreen
//
//  This class uses Sprite to show an animation.
//  Basically, it opens a large image and displays small pieces
//  of it on a sufficiently large speed to simulate movement.
//  
//  Keep in mind that it's your responsability to call the functions
//  at a nice rate.
//  Also, you should refresh the screen regularly to see any changes.
//
//  Basically, you should do this:
//    Animation animation("path/to/image.png", width, height, numberOfFrames);
//      // on a loop...
//      animation.nextFrame();
//      animation.render(x, y);
//
//      // refresh screen
//      SDL_Delay(delay);
//
// This will create and animation and keep refreshing it. Don't worry,
// when it gets on the last frame, it'll restart flawlessly.

#ifndef ANIMATION_H_DEFINED
#define ANIMATION_H_DEFINED

#include "SDLManager.hpp"
#include "Sprite.hpp"

/// Deals with an animation based on a spritesheet
class Animation
{
public:
	/// Starts an animation based on #filepath, with #ammount sprites with
	/// #width each.
	Animation(std::string filepath, int width, int height, int ammount);

    virtual ~Animation();

	/// Actually loads into memory all the stuff.
	//  @note It's called internally, don't bother with this.
	bool load();

	/// Makes animation go to next frame.
	//  If it ever gets to the last, will restart.
	void nextFrame();

	/// Makes animation go to previous frame.
	//  If it ever gets to the first frame, will restart backwards.
    void prevFrame();

	/// Makes animation restart to first frame.
    void restart();

	/// Makes animation go to the last frame.
	void goToLast();

	/// Places the current sprite onscreen.
	//  Screen needs to be refreshed, though.
	void render(int x=0, int y=0);

	/// Sets a RGB color on all sprites of this animation as transparent.
	//  This means when printing this image, this color will be
	//  passed-through and look invisible.
	void setTransparentRGBColor(int red=255, int green=0, int blue=255);

private:
    int rate;
    int curFrame;
	int maxFrame;
    int frameWidth;
    int frameHeight;
    std::string filepath;
	Sprite*     sprite;
	SDL_Rect*   frames;
};

#endif /* ANIMATION_H_DEFINED */
