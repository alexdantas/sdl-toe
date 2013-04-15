#include "Player.hpp"

Player::Player(int x, int y)
{
    int speed = 250;
    this->walking       = new Animation("img/andando.png", 20, 39, 5, speed);
    this->walking_other = new Animation("img/andando-outro-lado.png", 20, 39, 5, speed);
    this->jumping       = new Animation("img/pulando.png", 27, 39, 5, speed);

    this->current = walking;
    this->current->start();

	setPosition(x, y);
    this->velX = 0;
    this->velY = 0;
}
void Player::nextAnimation()
{
    this->current->stop();

	if (this->current == walking)
        this->current = walking_other;

    else if (this->current == walking_other)
        this->current = jumping;

	else if (this->current == jumping)
        this->current = walking_other;

    this->current->start();
}
Player::~Player()
{
//	if (this->animation) delete this->animation;
}
void Player::show()
{
    this->current->animate();
	this->current->render(this->x, this->y);
}
void Player::setPosition(int x=0, int y=0)
{
	this->x = x;
	this->y = y;
}
