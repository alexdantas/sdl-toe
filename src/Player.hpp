
#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "Sprite.hpp"
#include "Animation.hpp"
#include "VisibleObject.hpp"

class Player: public VisibleObject
{
public:


    enum AnimationState { STOPPED=0, WALKING_RIGHT=1,
                          WALKING_LEFT=2, JUMPING_RIGHT=3, JUMPING_LEFT=4 };

	/// Initializes the Player with all default values.
	Player(float x=0, float y=0);
	virtual ~Player();

	/// Animates and shows the player onscreen.
	void show();

	void update();
	void sufferGravity(float g=0);
	void jump();
	void changeAnimation(Player::AnimationState animation);

private:

	float velX;

	float velY;

	bool isJumping;

    /// Current state of the player
    Player::AnimationState currentState;

	/// Current animation the player's having.
	Animation*	current;

    /// All possible animations the player can have.
    Animation*  animation[5];
};

#endif /* PLAYER_H_DEFINED */
