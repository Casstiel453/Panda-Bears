#ifndef HOWTOPLAYSTATE_H
#define HOWTOPLAYSTATE_H

#include <iostream>
#include "State.h"

/** Class that derives from State */
class HowToPlayState :public State
{
private:

	sf::Font font;
	sf::Text text;

	TextureManager input;
	sf::Sprite inputSprite;

	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

	/**The function sets all parameters of the text
	*/
	void initText();


public:

	/*constructor for HowToPlayState*/
	HowToPlayState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	/*destructor for HowToPlayState*/
	virtual ~HowToPlayState();

	/**Overrided function from class State
	*/
	void updateInput(const float& dt);

	/**Overrided function from class State
	*/
	void update(const float& dt);

	/**Overrided function from class State
	*/
	void render(sf::RenderTarget* target = NULL);
};

#endif
