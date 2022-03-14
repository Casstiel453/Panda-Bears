#include <iostream>

#include "LeaderboardState.h"

LeaderboardState::LeaderboardState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states) : State(window, suppportedKeys, states)
{
	this->initKeybinds();
	this->initTextures();
	this->initText();
	this->initFile();
	this->sortScores(scores);
}

LeaderboardState::~LeaderboardState()
{

}


void LeaderboardState::initFile()
{
	std::ifstream file("Highscore.txt", std::ios::in);

		if (!file)
			throw FileMissingException();
		while (file >> playerName >> score)
		{
			this->scores.push_back(std::make_pair(playerName, score));
		}
		if (scores.size() < 1)
			throw FileMissingException();
	

	file.close();

}

void LeaderboardState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void LeaderboardState::initTextures()
{
		playScreen.AddResource("background4");
		playSprite.setTexture(*(playScreen.GetResource("background4")));
}

void LeaderboardState::initText()
{
	text.setFont(font);
	font.loadFromFile("Crazy.ttf");
	text.setPosition(10,10);
	text.setString("Leaderboard:");
	text.setCharacterSize(58);
	text.setFillColor(sf::Color::Green);
	text.setStyle(sf::Text::Bold);
}

void LeaderboardState::updateInput(const float& dt)
{
	//update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybings.at("CLOSE"))))
	{
		this->endState();
	}
}

void LeaderboardState::update(const float& dt)
{
	this->updateInput(dt);

}

void LeaderboardState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	target->draw(playSprite); //display background of LeaderboardState
	target->draw(text); //display text of LeaderboardState
	this->renderScores(target);
}

void LeaderboardState::renderScores(sf::RenderTarget* target)
{
	float y = 30.f;
	for (auto it = scores.begin(); it != scores.end(); it++)
	{
		if (std::distance(scores.begin(), it) < 20)
		{
			textFromInput.setFont(font);
			textFromInput.setPosition(sf::Vector2f(10.f, y += 30.f));
			textFromInput.setFillColor(sf::Color::Black);
			textFromInput.setString(std::to_string(it->second) + " ------ " + it->first);
			textFromInput.setCharacterSize(40);
			textFromInput.setStyle(sf::Text::Bold);
			target->draw(textFromInput);
		}
	}
}

void LeaderboardState::sortScores(std::vector<std::pair<std::string, int>>& scores)
{
	sort(scores.rbegin(), scores.rend(), [](auto& left, auto& right)
		{
			return left.second < right.second;
		}
	);
}