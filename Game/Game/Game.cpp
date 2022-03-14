#include <iostream>
#include "Game.h"
#include "State.h"
#include "OptionsState.h"


Game::Game()
{
	this->init();
	this->initKeys();
	this->initStates();
	this->updateSFMLEvents();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

void Game::init()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Panda Bears");
	this->window->setFramerateLimit(120);
}

void Game::initStates()
{
	try
	{
		this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states, this->playerName));
	}
	catch (FileMissingException& e)
	{
		std::cerr << e.what() << "\n";
	}
}

void Game::initKeys()
{
	this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
}

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	
	}
}

void Game::update()
{
	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else //app end completely
	{
	
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();
	if (!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}