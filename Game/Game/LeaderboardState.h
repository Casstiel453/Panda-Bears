#ifndef LEADERBOARDSTATE_H
#define LEADERBOARDSTATE_H

#include <iostream>
#include "State.h"
#include "FileMissingException.h"

/** Class that derives from State */
class LeaderboardState :public State
{
private:

	int score;
	sf::Font font;
	sf::Text text;
	sf::Text textFromInput;
	std::string playerName;
	
	TextureManager input;
	sf::Sprite inputSprite;

	std::vector<std::pair<std::string, int>> scores;
	
	/**Overrided function from class State
	*/
	void initKeybinds();

	/**The function initializes all textures for this state
	*/
	void initTextures();

	/**The function sets all parameters of the text
	*/
	void initText();

	/**The function open text file and constructs a pair objects
	*/
	void initFile();

public:

	/*constructor for LeaderboardState*/
	LeaderboardState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

	/*destructor for LeaderboardState*/
	virtual ~LeaderboardState();

	/** The function set the parameters of the scores
	@param target pointer to the target
	*/
	void renderScores(sf::RenderTarget* target);

	/** The function set the parameters of the scores
	@param scores reference to a vector of pair
	*/
	void sortScores(std::vector<std::pair<std::string, int>>& scores);

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
