#include "Panda.h"


Panda::Panda(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("Stayin", 10.f, 0, 0, 11, 0, 190, 246);

	this->pandaState = PND_IDLE;

	this->updateStats(true);

	this->keytime = 0.f;
	this->keytimeMax = 10.f;

}

Panda::~Panda()
{
	delete this->animationComponent;
}


void Panda::initVariables()
{
	this->animationComponent = NULL;
}

void Panda::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Panda::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);

}

const bool Panda::isPressed() const
{
	if (this->pandaState == PND_ACTIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Panda::setIdle()
{
	this->pandaState = PND_IDLE;
}

void Panda::setActive()
{
	this->pandaState = PND_ACTIVE;
	//std::cout << "set active";
}


void Panda::updatePandas(const sf::Vector2f mousePos)
{
	//in which state is button - depending of mouse position

	if (this->sprite.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
		{
			this->pandaState = PND_PRESSED;
		//	std::cout << "panda active";
		}
	}

}


const bool Panda::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void Panda::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 50.f * dt;
}

void Panda::update(const float& dt)
{
	this->animationComponent->play("Stayin", dt);

	this->updateKeytime(dt);

}

void Panda::setPosition(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void Panda::render(sf::RenderTarget* target)
{
		target->draw(this->sprite);
}

void Panda::loseHunger(const int hunger)
{
		this->hunger -= hunger;
		if (this->hunger < 0)
		{
			this->hunger = 0;
		}
}

void Panda::loseBoredom(const int boredom)
{
	this->boredom -= boredom;
	if (this->boredom < 0)
	{
		this->boredom = 0;
	}
}

void Panda::loseFatigue(const int fatigue)
{
	this->fatigue -= fatigue;
	if (this->fatigue < 0)
	{
		this->fatigue = 0;
	}
}

void Panda::gainHunger(const int hunger)
{
		this->hunger += hunger;
	
		if (this->hunger > this->hungerMax)
		{
			this->hunger = this->hungerMax;
			
		}
}

void Panda::gainBoredom(const int boredom)
{
	this->boredom += boredom;

	if (this->boredom > this->boredomMax)
	{
		this->boredom = this->boredomMax;
	}
}

void Panda::gainFatigue(const int fatigue)
{
	this->fatigue += fatigue;

	if (this->fatigue > this->fatigueMax)
	{
		this->fatigue = this->fatigueMax;
	}
}

bool Panda::checkStats()
{
	if (this->hunger <= 0)
	{
		return true;
	}
	else if (this->boredom <= 0)
	{
		return true;
	}
	else if (this->fatigue <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Panda::updateStats(const bool reset)
{
	this->hungerMax = 3000;
	if (reset)
	this->hunger = this->hungerMax;


	this->boredomMax = 3000;
	if (reset)
		this->boredom = this->boredomMax;


	this->fatigueMax = 3000;
	if (reset)
		this->fatigue = this->fatigueMax;
}