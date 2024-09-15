// Header Guards
#ifndef SCOREBOARD
#define SCOREBOARD

// Bibliotheken
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream> 

// struct
struct ScoreEntry {
	std::string playerName;
	int playerScore;

	ScoreEntry(const std::string& name, int score)
		: playerName(name), playerScore(score) {}

	// Vergleichsoperator für Sortierung
	bool operator<(const ScoreEntry& other) const {
		return playerScore > other.playerScore;
	}
};

// Klasse Scoreboard
class Scoreboard {
public:
	// Constructor
	Scoreboard();

	//EVA
	int input(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

	// Funktionen für das Eintragen und Laden von Highscores
	void addScore(const std::string& playerName, int score);
	void loadScores();
	void saveScores();
	void clearScores();

private:
	// Instanzen
	sf::Font font;
	sf::Text titleText;
	sf::Text deleteText;
	sf::Text returnText;
	std::vector<ScoreEntry> scores;

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