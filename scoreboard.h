/* LUMALU
*/
#ifndef SCOREBOARD
#define SCOREBOARD

#include <SFML/Graphics.hpp>



class Scoreboard {
public:
	Scoreboard();
	int handleInput(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

private:
	sf::Font font;
	sf::Text titleText;

	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
