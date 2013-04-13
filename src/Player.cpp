
#include "Player.hpp"

Player::Player(int x=0, int y=0)
{
	this->sprite = new Sprite(SPRITE_IMAGE_PATH);
	this->sprite->load();
	this->sprite->setTransparentRGBColor(0xFF, 0xFF, 0xFF);

	setPosition(x, y);
    this->velX = 0;
    this->velY = 0;
}
Player::~Player()
{
	delete this->sprite;
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

