#include "Player.hpp"

Player::Player(int x=0, int y=0)
{
	this->sprite = new Sprite(SPRITE_IMAGE_PATH);
	this->sprite->setTransparentRGBColor(255, 255, 255);
    
    this->animation = new Animation("img/andando.png", 20, 39, 5);

	setPosition(x, y);
    this->velX = 0;
    this->velY = 0;
}
Player::~Player()
{
	if (this->sprite) delete this->sprite;
	if (this->animation) delete this->animation;    
}
void Player::show()
{
	this->sprite->render(this->x, this->y);
}
void Player::setPosition(int x=0, int y=0)
{
	this->x = x;
	this->y = y;
}

