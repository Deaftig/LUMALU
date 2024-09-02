// Header Guards
#ifndef SCOREBOARD
#define SCOREBOARD

// Bibliotheken
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Klasse Scoreboard
class Scoreboard {
public:
	// Constructor
	Scoreboard();

	//EVA
	int input(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

	struct scoreboard { std::string scoreboardName; int scoreboardScore; };

private:
	// Instanzen
	sf::Font font;
	sf::Text titleText;
	sf::Text deleteText;
	sf::Text returnText;

	// Variablen
	int selectedScoreboardItem = 0;

	// EVA
	// Eingabe
	int processState(sf::Event& event);
	// Verarbeitung
	void updateTextColors();
	// Ausgabe
	void renderText(sf::RenderWindow& window);

	// Funktionen
	void initTextStrings();
	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};
#endif