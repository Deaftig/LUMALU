/* LUMALU
*/
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <vector>


class Game {
public:
	Game();
	int handleInput(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text scoreText;
	sf::CircleShape fruit;
	sf::Clock moveClock;
	sf::Time moveInterval;

	std::vector<sf::Vector2i> snake;
	sf::Vector2i direction;

	bool fruitActive = false;
	bool snakeActive = false;

	void spawnFruit();
	void spawnSnake();

	void updateFruit();
	void updateSnake();

	void renderArena(sf::RenderWindow& window);
	void renderFruit(sf::RenderWindow& window);
	void renderSnake(sf::RenderWindow& window);

	void initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
