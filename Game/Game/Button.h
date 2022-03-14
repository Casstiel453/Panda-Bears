#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "TextureManager.h"

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

/** Button class */
class Button
{
private:

	short unsigned buttonState;

	TextureManager button;
	sf::Sprite buttonSprite;

	float keytime;
	float keytimeMax;

public:

	/*constructor for Button*/
	Button(float x, float y, float width, float height, std::string text);

	/*destructor for Button*/
	virtual ~Button();

	/**The function returns bool value, true if button is active
	*/
	const bool isPressed() const;

	/**The function setting key time and returns bool value
	*/
	const bool getKeytime();

	/**The function updates key time
	@param dt reference to the delta time
	*/
	virtual void updateKeytime(const float& dt);

	/** The function renders button
	@param target pointer to the target
	*/
	void render(sf::RenderTarget* target);

	/** The function updates button, checks is it pressed and sets its state
	@param mousePos coordinates of mouse
	@param dt reference to the delta time
	*/
	void update(const sf::Vector2f mousePos, const float& dt);


};

#endif
