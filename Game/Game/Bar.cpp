#include "Bar.h"

Bar::Bar(Panda* panda, float width, float height, float x, float y) 
{
	this->panda = panda;
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->initHungerBar();
	this->initBoredomBar();
	this->initFatigueBar();
}

Bar::~Bar()
{
}


void Bar::initHungerBar()
{
	this->barMaxWidth = width;

	this->hungerBarText.setFont(this->font);
	font.loadFromFile("Crazy.ttf");

	this->hungerBarBack.setSize(sf::Vector2f(width, height));
	this->hungerBarBack.setFillColor(sf::Color(50,50,50,200));
	this->hungerBarBack.setPosition(x,y-60);

	this->hungerBarFront.setSize(sf::Vector2f(width, height));
	this->hungerBarFront.setFillColor(sf::Color(250, 20, 20, 200));
	this->hungerBarFront.setPosition(this->hungerBarBack.getPosition());

	this->hungerBarText.setPosition(this->hungerBarFront.getPosition().x, this->hungerBarFront.getPosition().y - 31.f);

	hungerBarText.setFillColor(sf::Color::Black);
	hungerBarText.setStyle(sf::Text::Bold);
}

void Bar::initBoredomBar()
{
	this->boredomBarText.setFont(this->font);

	this->boredomBarBack.setSize(sf::Vector2f(width, height));
	this->boredomBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->boredomBarBack.setPosition(x, y - 25);

	this->boredomBarFront.setSize(sf::Vector2f(width, height));
	this->boredomBarFront.setFillColor(sf::Color(250, 20, 20, 200));
	this->boredomBarFront.setPosition(this->boredomBarBack.getPosition());

	this->boredomBarText.setPosition(this->boredomBarFront.getPosition().x, this->boredomBarFront.getPosition().y - 31.f);

	boredomBarText.setFillColor(sf::Color::Black);
	boredomBarText.setStyle(sf::Text::Bold);
}

void Bar::initFatigueBar()
{
	this->fatigueBarText.setFont(this->font);

	this->fatigueBarBack.setSize(sf::Vector2f(width, height));
	this->fatigueBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->fatigueBarBack.setPosition(x, y+10);

	this->fatigueBarFront.setSize(sf::Vector2f(width, height));
	this->fatigueBarFront.setFillColor(sf::Color(250, 20, 20, 200));
	this->fatigueBarFront.setPosition(this->fatigueBarBack.getPosition());

	this->fatigueBarText.setPosition(this->fatigueBarFront.getPosition().x, this->fatigueBarFront.getPosition().y - 31.f);

	fatigueBarText.setFillColor(sf::Color::Black);
	fatigueBarText.setStyle(sf::Text::Bold);
}


void Bar::updateHungerBar()
{
	float percent = static_cast<float> (this->panda->hunger) / static_cast<float> (this->panda->hungerMax);
	this->hungerBarFront.setSize(sf::Vector2f(static_cast<float> (std::floor (this->barMaxWidth * percent)), this->hungerBarFront.getSize().y));

	this->hungerBarText.setString("HUNGER");
}

void Bar::updateBoredomBar()
{
	float percent = static_cast<float> (this->panda->boredom) / static_cast<float> (this->panda->boredomMax);
	this->boredomBarFront.setSize(sf::Vector2f(static_cast<float> (std::floor(this->barMaxWidth * percent)), this->boredomBarFront.getSize().y));

	this->boredomBarText.setString("BOREDOM");
}

void Bar::updateFatigueBar()
{
	float percent = static_cast<float> (this->panda->fatigue) / static_cast<float> (this->panda->fatigueMax);
	this->fatigueBarFront.setSize(sf::Vector2f(static_cast<float> (std::floor(this->barMaxWidth * percent)), this->fatigueBarFront.getSize().y));

	this->fatigueBarText.setString("FATIGUE");
}


void Bar::update(const float& dt)
{
	this->updateHungerBar();
	this->updateBoredomBar();
	this->updateFatigueBar();
}

void Bar::render(sf::RenderTarget& target)
{
	target.draw(this->hungerBarBack);
	target.draw(this->hungerBarFront);
	target.draw(this->hungerBarText);

	target.draw(this->boredomBarBack);
	target.draw(this->boredomBarFront);
	target.draw(this->boredomBarText);

	target.draw(this->fatigueBarBack);
	target.draw(this->fatigueBarFront);
	target.draw(this->fatigueBarText);
}

