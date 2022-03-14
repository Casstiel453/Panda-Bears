#include "Player.h"


Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	
	this->setPosition(x, y);

	this->createAnimationComponent( texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 5, 0, 190, 246);

	//this->animationComponent->addAnimation("YAWN_LEFT", 10.f, 0, 0, 11, 0, 190, 246);

}

Player::~Player()
{


}

void Player::initVariables()
{

}

void Player::initComponents()
{
}

void Player::update(const float& dt)
{
	
	/*
	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE)
	{
	this->animationComponent->play("IDLE",dt);
	}
	else if...
	
	*/


	this->animationComponent->play("IDLE_LEFT", dt);
//	this->animationComponent->play("YAWN_LEFT", dt);

}

