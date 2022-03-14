#include <iostream>

#include "GameState.h"
#include "GameOverState.h"
#include "TextureManager.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* suppportedKeys, std::stack<State*>* states, std::string playerName): State(window, suppportedKeys, states)
{
	this->playerName = playerName;
	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
	this->initBar();
	this->initButtons();
	this->initText();
}

GameState::~GameState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->panda.begin();
	for (it2 = this->panda.begin(); it2 != this->panda.end(); ++it2)
	{
		delete it2->second;
	}
	auto it3 = this->bar.begin();
	for (it3 = this->bar.begin(); it3 != this->bar.end(); ++it3)
	{
		delete it3->second;
	}
}

void GameState::initKeybinds()
{
	this->keybings["CLOSE"] = this->supportedKeys->at("Escape");
}

void GameState::initText()
{
	font.loadFromFile("Crazy.ttf");
	text.setFont(font);
	text.setPosition(550, 360);
	text.setCharacterSize(53);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);

	text2.setFont(font);
	text2.setPosition(400, 360);
	text2.setString("Score: ");
	text2.setCharacterSize(53);
	text2.setFillColor(sf::Color::Black);
	text2.setStyle(sf::Text::Bold);

	text3.setFont(font);
	text3.setPosition(50, 360);
	text3.setString(playerName);
	text3.setCharacterSize(53);
	text3.setFillColor(sf::Color::Black);
	text3.setStyle(sf::Text::Bold);
}

void GameState::initTextures()
{
	playScreen.AddResource("gameStateBackground");
	playSprite.setTexture(*(playScreen.GetResource("gameStateBackground")));

	if (!this->textures["PLAYER_SHEET"].loadFromFile("PandaBreathingSheet.png"))
	{
		throw FileMissingException();
	}

	if (!this->textures["PLAYER_SHEET2"].loadFromFile("PandaYawingSheet.png"))
	{
		throw FileMissingException();
	}

	if (!this->textures["PLAYER_SHEET3"].loadFromFile("PandaHungrySheet.png"))
	{
		throw FileMissingException();
	}
}

void GameState::initBar()
{
	this->bar["Player1Bar"] = new Bar(this->panda["Player1"], 170.f, 10.f, 90.f, 80.f);
	this->bar["Player2Bar"] = new Bar(this->panda["Player2"], 170.f, 10.f, 320.f, 100.f);
	this->bar["Player3Bar"] = new Bar(this->panda["Player3"], 170.f, 10.f, 550.f, 80.f);
}

void GameState::initPlayers()
{

	this->panda["Player1"] = new Panda(80, 100, this->textures["PLAYER_SHEET"]);
	this->panda["Player2"] = new Panda(310, 120, this->textures["PLAYER_SHEET2"]);
	this->panda["Player3"] = new Panda(540, 100, this->textures["PLAYER_SHEET3"]);

}

void GameState::initButtons()
{
	this->buttons["Eat_state"] = new Button(0, 422, 1, 1, "eat");
	this->buttons["Fun_state"] = new Button(267, 422, 1, 1, "fun");
	this->buttons["Sleep_state"] = new Button(534, 422, 1, 1, "sleep");
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybings.at("CLOSE"))))
	{
		this->endState();
	}
		
	this->panda["Player1"]->loseHunger(1);
	this->panda["Player1"]->loseBoredom(2);
	this->panda["Player1"]->loseFatigue(1);

	this->panda["Player2"]->loseHunger(1);
	this->panda["Player2"]->loseBoredom(1);
	this->panda["Player2"]->loseFatigue(2);

	this->panda["Player3"]->loseHunger(2);
	this->panda["Player3"]->loseBoredom(1);
	this->panda["Player3"]->loseFatigue(1);
try
{
	if (this->panda["Player1"]->checkStats() || this->panda["Player2"]->checkStats() || this->panda["Player3"]->checkStats())
	{
		try
		{
			this->states->push(new GameOverState(this->window, this->supportedKeys, this->states, this->score, this->playerName));
		}
		catch (FileMissingException& e)
		{
			std::cerr << e.what() << "\n";
		}
	}
}
catch (FileMissingException& e)
{
	std::cerr << e.what() << "\n";
}
}

void GameState::updateButtons(const float& dt, std::string name)
{

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView, dt);
	}

	//quit the game
	if (this->buttons["Eat_state"]->isPressed())
	{
		this->panda[name]->gainHunger(500);
	}

	if (this->buttons["Fun_state"]->isPressed())
	{
		this->panda[name]->gainBoredom(500);
	}

	if (this->buttons["Sleep_state"]->isPressed())
	{
		this->panda[name]->gainFatigue(500);
	}

}

void GameState::updatePandas(const float& dt)
{
	for (auto& it : this->panda)
	{
		it.second->updatePandas(this->mousePosView);
	}

	if (this->panda["Player1"]->pandaState == PND_PRESSED)
	{	
		this->panda["Player1"]->setActive();
		this->panda["Player3"]->setIdle();
		this->panda["Player2"]->setIdle();

	}
	if (this->panda["Player1"]->pandaState == PND_ACTIVE)
	{
		this->updateButtons(dt, "Player1");
	}

	if (this->panda["Player2"]->pandaState == PND_PRESSED)
	{
		this->panda["Player2"]->setActive();
		this->panda["Player1"]->setIdle();
		this->panda["Player3"]->setIdle();
		this->updateButtons(dt, "Player2");
	
	}
	if (this->panda["Player2"]->pandaState == PND_ACTIVE)
	{
		this->updateButtons(dt, "Player2");
	}


	if(this->panda["Player3"]->pandaState == PND_PRESSED)
	{
		this->panda["Player3"]->setActive();
		this->panda["Player1"]->setIdle();
		this->panda["Player2"]->setIdle();
		this->updateButtons(dt, "Player3");

	}
	if (this->panda["Player3"]->pandaState == PND_ACTIVE)
	{
		this->updateButtons(dt, "Player3");
	}
}

void GameState::updateScore()
{
	sf::Time time = clock.getElapsedTime();
	score = static_cast<int>(time.asSeconds());
	//std::cout << score << std::endl;

	std::stringstream ss;
	ss << score;
	str = ss.str();
	text.setString(str);
}

void GameState::update(const float& dt)
{
		this->updateScore();
		this->updateMousePosition();
		this->updateInput(dt);

		this->panda["Player1"]->update(dt);
		this->panda["Player2"]->update(dt);
		this->panda["Player3"]->update(dt);

		this->bar["Player1Bar"]->update(dt);
		this->bar["Player2Bar"]->update(dt);
		this->bar["Player3Bar"]->update(dt);

		this->updatePandas(dt);

	//	this->updateButtons(dt);

}

void GameState::render(sf::RenderTarget* target )
{

	if(!target)
	{
		target = this->window;
	}
	
	target->draw(playSprite); //display background of gameState

	this->panda["Player1"]->render(target);//display player1
 	this->panda["Player2"]->render(target);//display player2
	this->panda["Player3"]->render(target);//display player

	this->bar["Player1Bar"]->render(*target);//display button
	this->bar["Player2Bar"]->render(*target);
	this->bar["Player3Bar"]->render(*target);

	this->renderButtons(target);//display button
	target->draw(text); //display text
	target->draw(text2); //display text
	target->draw(text3); //display text

}

void GameState::renderPandas(sf::RenderTarget* target)
{
	for (auto& it : this->panda)
	{
		it.second->render(target);
	}
}

void GameState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
