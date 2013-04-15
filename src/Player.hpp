
#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "Sprite.hpp"
#include "Animation.hpp"

class Player
{
public:
    /// Initializes the Player with all default values.
    Player(int x=0, int y=0);
    virtual ~Player();

    /// Animates and shows the player onscreen.
	void show();

    /// Sets the current position to #x and #y.
	void setPosition(int x, int y);

    /// Makes the player start the next possible animation.
    //  @warning This should be used for debugging purposes only.
	void nextAnimation();

private:
	int x;
    int y;
    int velX;
    int velY;

    Animation*  current; ///< Current animation the player's having
    Animation*  walking;
    Animation*  walking_other;
    Animation*  jumping;
};

#endif /* PLAYER_H_DEFINED */
