#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>

class Scoreboard
{
public:
	Scoreboard();
	void render(sf::RenderWindow& window);
	int handleInput(sf::Event event);
private:
};

#endif
