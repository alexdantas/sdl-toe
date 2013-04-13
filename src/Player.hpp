
#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "Sprite.hpp"
#include "Animation.hpp"

/// Where the player's sprite's located
#define SPRITE_IMAGE_PATH "img/mario.png"

class Player
{
public:
    Player(int x, int y);
    virtual ~Player();

	void show();
	void setPosition(int x, int y);
    Animation* animation;
    
private:
	int x; int y;
    int velX; int velY;
	Sprite* sprite;
};

#endif /* PLAYER_H_DEFINED */

