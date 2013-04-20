
#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "Sprite.hpp"
#include "Animation.hpp"

class Player
{
public:
	/// Initializes the Player with all default values.
	Player(float x=0, float y=0);
	virtual ~Player();

	/// Animates and shows the player onscreen.
	void show();

	/// Sets the current position to #x and #y.
	void setPosition(float x, float y);

	/// Makes the player start the next possible animation.
	//	@warning This should be used for debugging purposes only.
	void nextAnimation();

	void moveDown(float x);
	void moveUp(float x);
	void moveLeft(float x);
	void moveRight(float x);

	void update();
	void sufferGravity(float g=0);
	void jump();

private:
	float x;
	float y;
	float velX;
	float velY;
	bool isJumping;

	Animation*	current; ///< Current animation the player's having
	Animation*	walking;
	Animation*	walking_other;
	Animation*	jumping;
};

#endif /* PLAYER_H_DEFINED */
