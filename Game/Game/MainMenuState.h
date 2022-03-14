#ifndef MAINMENUSTATE_H_INCLUDED
#define MAINMENUSTATE_H_INCLUDED

#include "TextureManager.h"
#include "GameState.h"
#include "Panda.h"
#include "Button.h"
#include "FileMissingException.h"

/** Class that derives from State */
class MainMenuState :public State
{
private:

	sf::Font font;
	std::map<std::string, Button*> buttons;
	std::string playerName;
	
	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

	/**The function initializes buttons
	*/
	void initButtons(); 

public:

	/*constructor for MainMenuState*/
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string playerName);

	/*destructor for MainMenuState*/
	virtual ~MainMenuState();

	/**Overrided function from class State
	*/
	void updateInput(const float& dt);

	/** The function updates buttons
	@param dt reference to the delta time
	*/
	void updateButtons(const float& dt);

	/**Overrided function from class State
	*/
	void update(const float& dt);

	/** The function renders buttons
	@param target pointer to the target
	*/
	void renderButtons(sf::RenderTarget* target = NULL);

	/**Overrided function from class State
	*/
	void render(sf::RenderTarget* target = NULL);

};

#endif
