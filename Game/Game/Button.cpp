#include "Button.h"

Button::Button(float x, float y, float width, float height, std::string text)
{
	button.AddResource(text);
	buttonSprite.setTexture(*(button.GetResource(text)));

	this->buttonState = BTN_IDLE;

	this->buttonSprite.setPosition(sf::Vector2f(x, y));
	this->buttonSprite.setScale(sf::Vector2f(width, height));

	this->keytime = 0.f;
	this->keytimeMax = 20.f;
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::render(sf::RenderTarget* target)
{
//	target->draw(this->shape);
	target->draw(buttonSprite);
}


const bool Button::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void Button::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 80.f * dt;
}


void Button::update(const sf::Vector2f mousePos, const float& dt)
{
	this->updateKeytime(dt);

	//in which state is button - depending of mouse position
	this->buttonState = BTN_IDLE;

	if (this->buttonSprite.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
		{
			this->buttonState = BTN_ACTIVE;
		//	std::cout << "PRESSSED" << std::endl;
		}
		
	}

	// color of buttons in every state
	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->buttonSprite.setColor(sf::Color::White);
		break;
	case BTN_HOVER:
		this->buttonSprite.setColor(sf::Color::Cyan);
		break;
	case BTN_ACTIVE:
		this->buttonSprite.setColor(sf::Color::Blue);
		break; 
	default:
		this->buttonSprite.setColor(sf::Color::Blue);
		break;
	}
}