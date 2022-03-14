#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "MainMenuState.h"
#include "Panda.h"
#include "GameOverState.h"
#include "FileMissingException.h"


/** Main class */
class Game
{
private:

	float dt;
	Panda* panda;
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	std::string playerName;

	std::stack<State*> states;
	std::map<std::string,int> supportedKeys;

	/** The function initializes window and sets fremrates
	*/
	void init();

	/** The function initializes supported keys
	*/
	void initKeys();

	/** The function initializes stack with states, pushes Main Menu at the top
	*/
	void initStates();
	
public:

	/*constructor for Game*/
	Game(); 

	/*destructor for Game*/
	virtual ~Game();

	/** The function update delta time
	*/
	void updateDt();
	
	/** The function update SFML events
	*/
	void updateSFMLEvents();
	
	/** The function update states of the game
	*/
	void update();

	/** The function renders game
	*/
	void render();

	/** The function update game until it is running
	*/
	void run();
};

#endif