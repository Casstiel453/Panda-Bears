#include <iostream>

#include "HowToPlayState.h"

HowToPlayState::HowToPlayState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states) : State(window, suppportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initText();
}

HowToPlayState::~HowToPlayState()
{

}

void HowToPlayState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void HowToPlayState::initTextures()
{
	
		playScreen.AddResource("background3");
		playSprite.setTexture(*(playScreen.GetResource("background3")));
	
}

void HowToPlayState::initText()
{
	text.setFont(font);
	font.loadFromFile("Crazy.ttf");
	text.setPosition(10, 120);
	text.setString("How to play?\nIt's easy.\nYou need to keep all three Panda\nbears alive.\nIt can be done by giving them\nadditional supplies.");
	text.setCharacterSize(58);
	text.setFillColor(sf::Color::Magenta);
	text.setStyle(sf::Text::Bold);
}

void HowToPlayState::updateInput(const float& dt)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybings.at("CLOSE"))))
	{
		this->endState();
	}
}

void HowToPlayState::update(const float& dt)
{
	this->updateInput(dt);
}

void HowToPlayState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(playSprite); //display background of HowToPlay
	target->draw(text); //display text
}
