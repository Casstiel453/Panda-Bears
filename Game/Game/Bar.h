#ifndef BAR_H_INCLUDED
#define BAR_H_INCLUDED

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Panda.h"

/** Bar class */
class Bar
{
private:

	sf::Font font;
	sf::Text hungerBarText, boredomBarText, fatigueBarText;

	Panda* panda;
	float width, height, x, y;
	float barMaxWidth;

	sf::RectangleShape hungerBarBack, hungerBarFront,
		boredomBarBack, boredomBarFront,
		fatigueBarBack, fatigueBarFront;

	/** The function initializes hunger bars
	*/
	void initHungerBar();
	
	/** The function initializes boredom bars
	*/
	void initBoredomBar();

	/** The function initializes fatigue bars
	*/
	void initFatigueBar();

public:

	/*constructor for Bar*/
	Bar(Panda* panda, float width, float height, float x,float y);
	
	/*destructor for Bar*/
	virtual ~Bar();

	/** The function updates hunger bar
	*/
	void updateHungerBar();

	/** The function updates boredom bar
	*/
	void updateBoredomBar();

	/** The function updates fatigue bar
	*/
	void updateFatigueBar();

	/** The function updates bars
	@param dt reference to the delta time
	*/
	void update(const float& dt);

	/** The function renders bars
	@param target pointer to the target
	*/
	void render(sf::RenderTarget& target);

};

#endif
