#include <iostream>

#include "MainMenuState.h"
#include "OptionsState.h"
#include "TextureManager.h"
#include <istream>
#include <regex> 

OptionsState::OptionsState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states) : State(window, suppportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	//this->updateSFMLEvents();
	//this->initPlayers();
	text.setFont(font);
	font.loadFromFile("Crazy.ttf");
	text.setPosition(310, 280);
	text.setCharacterSize(45);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	textAlert.setFont(font);
	textAlert.setPosition(230, 340);
	textAlert.setCharacterSize(30);
	textAlert.setFillColor(sf::Color::Blue);
	//textAlert.setStyle(sf::Text::Bold);

}

OptionsState::~OptionsState()
{
	
}

void OptionsState::updateSFMLEvents()
{	
	while (this->window->pollEvent(event))
	{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 123 && string.size() < 10 ) 
			{
				string += static_cast<char>(event.text.unicode);
				text.setString(string);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && string.size() > 0)
		{
			string.pop_back();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (nameCheck(string))
			{
				this->states->pop();
				this->states->push(new MainMenuState(this->window, this->supportedKeys, this->states, this->string));
			}
			else
				textAlert.setString("Incorrect player name.\nStart with ONE capital letter, \nfollowed only by small ones and numbers.\nMinimum 3 letters!");
		}
	}
}

bool OptionsState::nameCheck(std::string& name)
{
	if (std::regex_match(name, std::regex("[A-Z]{1}[a-z0-9]{2,}")))
		return true;
	else
		return false;
}


void OptionsState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void OptionsState::initTextures()
{
		playScreen.AddResource("background2");
		playSprite.setTexture(*(playScreen.GetResource("background2")));

		input.AddResource("player_name");
		inputSprite.setTexture(*(input.GetResource("player_name")));

		this->inputSprite.setPosition(sf::Vector2f(264, 200));

}

void OptionsState::updateInput(const float& dt)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybings.at("CLOSE"))))
	{
		this->endState();
	}

}

void OptionsState::update(const float& dt)
{

	this->updateMousePosition();
	this->updateInput(dt);
	this->updateSFMLEvents();

}

void OptionsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(playSprite); //display background of options
	target->draw(inputSprite); //texture playername
	target->draw(this->text); //display input text
	target->draw(this->textAlert); // alert regex
}
