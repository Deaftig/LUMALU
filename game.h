/* LUMALU
*/
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
	sf::Font font;
	sf::Text scoreText;
	sf::CircleShape fruit;

	int x, y = 0;
	bool activeFruit = false;
	
	void spawnFruit();
	void renderArena(sf::RenderWindow& window);
	void initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
