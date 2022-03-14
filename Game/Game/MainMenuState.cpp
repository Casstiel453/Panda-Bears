#include <iostream>
#include "State.h"

#include "MainMenuState.h"
#include "OptionsState.h"
#include "HowToPlayState.h"
#include "LeaderboardState.h"
#include "State.h"


MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states, std::string playerName) : State(window, suppportedKeys, states)
{
	
	this->initKeybinds();
	this->initTextures();
	this->initButtons();

if (playerName.empty())
	{
		this->playerName = "NoName";
	}
	else
		this->playerName = playerName;
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::initTextures()
{
	playScreen.AddResource("background");
	playSprite.setTexture(*(playScreen.GetResource("background")));
}

void MainMenuState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void MainMenuState::initButtons()
{
	this->buttons["New_game_state"] = new Button(340,300, 2,2,"start");
	this->buttons["Options_state"] = new Button(320, 350, 2, 2, "options");
	this->buttons["How_to_play_state"] = new Button(280, 400, 2, 2, "howtoplay");
	this->buttons["Leader_board_state"] = new Button(265, 455, 2, 2, "leaderboard");
	this->buttons["Exit_state"] = new Button(365, 507, 2, 2, "exit");
}

void MainMenuState::updateInput(const float& dt)
{
}


void MainMenuState::updateButtons(const float& dt)
{
	
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView, dt);
	}
	try
	{
		if (this->buttons["New_game_state"]->isPressed())
		{
			this->states->push(new GameState(this->window, this->supportedKeys, this->states, this->playerName));
		}

		if (this->buttons["Options_state"]->isPressed())
		{
			this->states->push(new OptionsState(this->window, this->supportedKeys, this->states));
		}
		if (this->buttons["How_to_play_state"]->isPressed())
		{
			this->states->push(new HowToPlayState(this->window, this->supportedKeys, this->states));
		}

		if (this->buttons["Leader_board_state"]->isPressed())
		{
			this->states->push(new LeaderboardState(this->window, this->supportedKeys, this->states));
		}
	}
	catch (FileMissingException& e)
	{
		std::cerr << e.what() << "\n";
	}
	//quit the game
	if (this->buttons["Exit_state"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePosition();

	this->updateInput(dt);

	this->updateButtons(dt);

}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	//display menu sprite
	target->draw(this->playSprite);

	this->renderButtons(target);
}
