#include "Player.hpp"

Player::Player(float x, float y): VisibleObject(x, y)
{
	VisibleObject(x, y); // parent constructor

	float speed = 120;

	this->animation[STOPPED]       = new Animation("img/standing.png", 15, 16, 1);
	this->animation[STOPPED]->setTransparentRGBColor(255, 255, 255);

	this->animation[WALKING_RIGHT] = new Animation("img/walking-right.png", 15, 16, 2, speed);
	this->animation[WALKING_RIGHT]->setTransparentRGBColor(255, 255, 255);

	this->animation[WALKING_LEFT]  = new Animation("img/walking-left.png", 15, 16, 2, speed);
	this->animation[WALKING_LEFT]->setTransparentRGBColor(255, 255, 255);

	this->animation[JUMPING_RIGHT] = new Animation("img/jumping-right.png", 16, 16, 1);
	this->animation[JUMPING_RIGHT]->setTransparentRGBColor(255, 255, 255);

	this->animation[JUMPING_LEFT]  = new Animation("img/jumping-left.png", 16, 16, 1);
	this->animation[JUMPING_LEFT]->setTransparentRGBColor(255, 255, 255);

//	this->walking		= new Animation("img/apterus-andando.png", 446, 398, 12, speed);

    this->currentState = STOPPED;
	this->current      = this->animation[STOPPED];
	this->current->start();

	setPosition(x, y);
	this->velX = 0;
	this->velY = 0;
	this->isJumping = true;
}
Player::~Player()
{
	if (this->animation[STOPPED])       delete this->animation[STOPPED];
	if (this->animation[WALKING_RIGHT]) delete this->animation[WALKING_RIGHT];
	if (this->animation[WALKING_LEFT])  delete this->animation[WALKING_LEFT];
	if (this->animation[JUMPING_RIGHT]) delete this->animation[JUMPING_RIGHT];
	if (this->animation[JUMPING_LEFT])  delete this->animation[JUMPING_LEFT];
}
void Player::show()
{
	this->current->animate();
	this->current->render((int)this->x, (int)this->y);
}
void Player::update()
{
//	this->sufferGravity(GRAVITY);
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
void Player::changeAnimation(Player::AnimationState animation)
{
    this->current->stop();

    this->currentState = animation;
	this->current      = this->animation[animation];
	this->current->start();
}

