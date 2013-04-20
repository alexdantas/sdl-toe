#include "Player.hpp"

Player::Player(float x, float y)
{
	float speed = 250;
	this->walking		= new Animation("img/andando.png", 20, 39, 5, speed);
	this->walking_other = new Animation("img/andando-outro-lado.png", 20, 39, 5, speed);
	this->jumping		= new Animation("img/pulando.png", 27, 39, 5, speed);

	this->current = walking;
	this->current->start();

	setPosition(x, y);
	this->velX = 0;
	this->velY = 0;
	this->isJumping = true;
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
	this->current->render((int)this->x, (int)this->y);
}
void Player::setPosition(float x=0, float y=0)
{
	this->x = x;
	this->y = y;
}
void Player::moveDown(float x)
{
	this->y -= x;
}
void Player::moveUp(float x)
{
	this->y += x;
}
void Player::moveLeft(float x)
{
	this->x -= x;
}
void Player::moveRight(float x)
{
	this->x += x;
}
void Player::update()
{
	this->sufferGravity(GRAVITY);
}
void Player::sufferGravity(float g)
{
	if (!this->isJumping) return;

	this->velY -= g;
	this->moveDown(this->velY);
}
void Player::jump()
{
	if (this->isJumping) return;

	this->isJumping = true;
	this->velY += 10;
}

