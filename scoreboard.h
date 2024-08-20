/* LUMALU
*/
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
	sf::Font font;
	sf::Text titleText;

	void initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
