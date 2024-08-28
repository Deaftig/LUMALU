/* LUMALU
*/
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

class Game
{
public:
	Game();
	void render(sf::RenderWindow& window);
	int handleInput(sf::Event& event);
	void update();

private:
	sf::Font font;
	sf::Text scoreText;
	sf::CircleShape fruit;

	std::vector<sf::Vector2i> snake;
	sf::Vector2i direction;

	void spawnFruit();
	void spawnSnake();
	void renderArena(sf::RenderWindow& window);
	void renderFruit(sf::RenderWindow& window);
	void renderSnake(sf::RenderWindow& window);

	void initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
