#include <iostream>

#include "GameOverState.h"


GameOverState::GameOverState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states, int score, std::string playerName) : State(window, suppportedKeys, states) 
{
	this->initKeybinds();
	this->initTextures();
	this->playerName = playerName;
	this->score = score;
	this->initText(score);
	this->setPosition(260, 150);

	this->createAnimationComponent(this->textures["PLAYER_SHEET_DEAD"]);

	this->animationComponent->addAnimation("PLAYER_SHEET_DEAD", 5.f, 0, 0, 23, 0, 285, 600);

}

GameOverState::~GameOverState()
{

}

void GameOverState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void GameOverState::initTextures()
{

	playScreen.AddResource("background5");
	playSprite.setTexture(*(playScreen.GetResource("background5")));

	if (!this->textures["PLAYER_SHEET_DEAD"].loadFromFile("PandaDeadSheet.png"))
	{
		throw FileMissingException();
	}
}

void GameOverState::initText(int score)
{
	std::stringstream ss;
	ss << score;
	std::string str = ss.str();
	text.setFont(font);
	font.loadFromFile("Crazy.ttf");
	text.setPosition(120, 275);
	text.setString("You killed Panda Bear :(\n    Your score is: " + str);
	text.setCharacterSize(58);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
}

void GameOverState::updateInput(const float& dt)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybings.at("CLOSE"))))
	{
		this->saveScore();
		this->states->pop();
		this->states->pop();
	}
}

void GameOverState::saveScore()
{
		std::ofstream file;
		file.open("Highscore.txt", std::ios::app);
		if (!file)
			throw FileMissingException();

		file << playerName << " " << score << "\n";
		file.close();

}

void GameOverState::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void GameOverState::update(const float& dt)
{
	this->updateInput(dt);
	this->animationComponent->play("PLAYER_SHEET_DEAD", dt);
}

void GameOverState::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void GameOverState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(playSprite); //display background of HowToPlay
	//target->draw(playSprite2); //display background of HowToPlay

	target->draw(this->sprite);
	target->draw(text); //display text

}
