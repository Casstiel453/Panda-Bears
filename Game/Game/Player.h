#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include"SFML\Graphics.hpp"
#include"Panda.h"


class Player : public Panda
{
private:
	short unsigned pandaState;
	void initVariables();
	void initComponents();
	//void initTextures();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	virtual void update(const float& dt);

};

#endif