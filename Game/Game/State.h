#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<vector>

#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"Player.h"
#include"TextureManager.h"

/** State class */
class State
{
protected:
	
	TextureManager playScreen;
	sf::Sprite playSprite;

	std::string playerName;
	std::stack<State*>* states;
	sf::RenderWindow* window;

	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybings;
	std::map<std::string, sf::Texture> textures;

	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	/** The function initializes supported keys
	*/
	virtual void initKeybinds() = 0;

public:

	/*constructor for State*/
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	/*destructor for State*/
	virtual ~State();

	/** The function updates mouse position
	*/
	virtual void updateMousePosition();

	/** The function updates player input
	@param dt reference to the delta time
	*/
	virtual void updateInput(const float& dt) = 0;

	/** The function updates game
	@param dt reference to the delta time
	*/
	virtual void update(const float& dt) = 0;

	/** The function renders game
	@param target pointer to the target
	*/
	virtual void render(sf::RenderTarget* target = NULL) = 0;

	/** The function returns bool value of quit
	*/
	const bool& getQuit() const;

	/** The function sets quit to true
	*/
	void endState();
};

#endif