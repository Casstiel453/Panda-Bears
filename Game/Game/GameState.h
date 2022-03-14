#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "Panda.h"
#include "Button.h"
#include "Bar.h"
#include "FileMissingException.h"

/** Class that derives from State */
class GameState :public State
{ 
private:

	std::map<std::string, Panda*> panda;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Bar*> bar;
	sf::Clock clock;
	int score;
	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
	std::string playerName;
	std::string str;
	sf::Time time;

	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

	/**The function initializes all players
	*/
	void initPlayers();

	/**The function initializes all bars
	*/
	void initBar();

	/**The function initializes all buttons
	*/
	void initButtons();

	/**The function sets all parameters of the text
	*/
	void initText(); 

public:
	
	/*constructor for GameState*/
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::string playerName);

	/*destructor for GameState*/
	virtual ~GameState();

	/**Overrided function from class State
	*/
	void update(const float& dt);

	/** The function updates player score 
	*/
	void updateScore();

	/**Overrided function from class State
	*/
	void updateInput(const float& dt);

	/** The function updates buttons
	@param dt reference to the delta time
	@param name of a player
	*/
	void updateButtons(const float& dt, std::string name);

	/** The function updates pandas
	@param dt reference to the delta time
	*/
	void updatePandas(const float& dt);

	/** The function renders buttons
	@param target pointer to the target
	*/
	void renderButtons(sf::RenderTarget* target = NULL);
	
	/**Overrided function from class State
	*/
	void render(sf::RenderTarget* target = NULL);
	
	/** The function renders pandas
	@param target pointer to the target
	*/
	void renderPandas(sf::RenderTarget* target = NULL);

};

#endif
