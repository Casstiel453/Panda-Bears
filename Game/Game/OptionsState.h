#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include <iostream>
#include "State.h"
#include "Button.h"
#include <regex>
#include <string>

/** Class that derives from State */
class OptionsState :public State
{
private:
	
	sf::Font font;
	sf::Event event;
	sf::Text text;
	sf::Text textAlert;
	std::string name;
	TextureManager input;
	sf::Sprite inputSprite;
	std::string string;

	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

public:

	/*constructor for OptionsState*/
	OptionsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	/*destructor for OptionsState*/
	virtual ~OptionsState();

	/** The function checks if player name is correctly inputed
	@param name reference to the name of the player
	*/
	bool nameCheck(std::string& name);

	/** The function update SFML events
	*/
	void updateSFMLEvents();

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
