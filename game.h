#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void render(sf::RenderWindow& window);
	int handleInput(sf::Event event);
private:
};

#endif
