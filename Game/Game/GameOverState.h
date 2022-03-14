#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <iostream>
#include "State.h"
#include "MainMenuState.h"
#include "AnimationComponent.h"
#include "FileMissingException.h"


/** Class that derives from State */
class GameOverState :public State
{
private:

	sf::Font font;
	sf::Text text;
	int score;
	int highScore;
	std::string name;
	sf::Sprite sprite;
	std::string playerName;
	AnimationComponent* animationComponent;
	TextureManager input;
	sf::Sprite inputSprite;

	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

	/**The function changes int to string and sets all parameters of the text
	@param score represents player score
	*/
	void initText(int score);

public:

	/*constructor for GameOverState*/
	GameOverState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, int score, std::string playerName);
	
	/*destructor for GameOverState*/
	virtual ~GameOverState();

	/** The function sets position of the object
	@param x position of the cursor on the X-axis
	@param y position of the cursor on the Y-axis
	*/
	void setPosition(const float x, const float y);

	/** The function saves player name and score in txt file
	*/
	void saveScore();

	/** The function creates animation component
	@param texture_sheet reference to texture
	*/
	void createAnimationComponent(sf::Texture& texture_sheet);

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
