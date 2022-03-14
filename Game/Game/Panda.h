#ifndef PANDA_H_INCLUDED
#define PANDA_H_INCLUDED

#include"SFML\Graphics.hpp"
#include "AnimationComponent.h"

enum panda_states { PND_IDLE = 0, PND_ACTIVE, PND_PRESSED };

/** Panda class */
class Panda
{
private:

	/**The function initializes variable
	*/
	void initVariables(); 

protected:

	sf::Sprite sprite;
	AnimationComponent* animationComponent;

public:
	//Stats
	short unsigned pandaState;
	int hunger;
	int hungerMax;
	int boredom;
	int boredomMax;
	int fatigue;
	int fatigueMax;

	float keytime;
	float keytimeMax;

	/**The function setting key time and returns bool value
	*/
	const bool getKeytime();

	/**The function updates key time
	@param dt reference to the delta time
	*/
	virtual void updateKeytime(const float& dt);

	/*constructor for Panda*/
	Panda(float x, float y, sf::Texture& texture_sheet);

	/*detructor for Panda*/
	virtual ~Panda();

	/**The function setting panda on the idle state
	*/
	void setIdle();

	/**The function setting panda on the active state
	*/
	void setActive();

	/**The function returns bool value if panda is active
	*/
	const bool isPressed() const;

	/**The function update panda, checks is it pressed and sets her state
	@param mousePos coordinates of mouse
	*/
	void updatePandas(const sf::Vector2f mousePos);

	/**The function setting texture
	@param texture reference to the texture
	*/
	void setTexture(sf::Texture& texture);

	/**The function creates new animation component
	@param texture_sheet reference to the texture
	*/
	void createAnimationComponent(sf::Texture& texture_sheet);

	/** The function sets position of the object
	@param x position of the cursor on the X-axis
	@param y position of the cursor on the Y-axis
	*/
	virtual void setPosition(const float x, const float y);

	/** The function updates animation and key time
	@param dt reference to the delta time
	*/
	void update(const float& dt);

	/** The function renders game
	@param target pointer to the target 
	*/
	void render(sf::RenderTarget* target =NULL) ;

	//Stats

	/** The function updates stats, setting their maximal value 
	@param reset reseting stats
	*/
	void updateStats(const bool reset);

	/** The function decreases hunger stats, sets it's minimal value to zero
	@param hunger current hunger
	*/
	void loseHunger(const int hunger);

	/** The function increases hunger stats, sets it's maximal value
	@param hunger current hunger
	*/
	void gainHunger(const int hunger);

	/** The function decreases boredom stats, sets it's minimal value to zero
	@param hunger current boredom
	*/
	void loseBoredom(const int boredom);

	/** The function increases boredom stats, sets it's maximal value
	@param hunger current boredom
	*/
	void gainBoredom(const int boredom);

	/** The function decreases fatigue stats, sets it's minimal value to zero
	@param hunger current fatigue
	*/
	void loseFatigue(const int fatigue);

	/** The function increases fatigue stats, sets it's maximal value
	@param hunger current fatigue
	*/
	void gainFatigue(const int fatigue);

	/** The function returns bool value, checks if one of the stats drops to zero or below zero
	*/
	bool checkStats();
};

#endif
