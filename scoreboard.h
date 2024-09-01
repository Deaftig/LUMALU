// Header Guards
#ifndef SCOREBOARD
#define SCOREBOARD

// Bibliotheken
#include <SFML/Graphics.hpp>
#include <iostream>

// Klasse Scoreboard
class Scoreboard {
public:
	// Funktionen
	Scoreboard();
	int input(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

private:
	// Instanzen
	sf::Font font;
	sf::Text titleText;
	sf::Text deleteText;
	sf::Text returnText;

	// Variablen
	int selectedScoreboardItem = 0;

	// Funktionen
	void initTextStrings();
	// EVA
	// Eingabe
	int processState(sf::Event& event);
	// Verarbeitung
	void updateTextColors();

	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};
#endif
