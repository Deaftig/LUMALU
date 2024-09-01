// Header Guards
#ifndef GAME
#define GAME

// Bibliotheken
#include <SFML/Graphics.hpp>
#include <vector>

// Klasse Game
class Game {
public:
	// Funktionen
	Game();
	int input(sf::Event& event);
	void update();
	void render(sf::RenderWindow& window);

private:
	// Instanzen
	sf::Font font;
	sf::Text finalText;
	sf::Text activeScoreText;
	sf::Text finalScoreText;
	sf::Text nameText;
	sf::Text againText;
	sf::Text returnText;
	sf::CircleShape fruit;
	sf::Clock moveClock;
	sf::Time moveInterval;
	std::vector<sf::Vector2i> snake;
	sf::Vector2i direction;

	std::string playerName;

	// Variablen
	bool fruitActive = false;
	bool snakeActive = false;
	bool gameOver = false;
	int playerScore = 0;
	bool growSnake = false;

	// Funktionen
	void initTextStrings();
	void spawnFruit();
	void spawnSnake();
	// EVA
	// Eingabe
	int processState(sf::Event& event);
	int processState_gameOver(sf::Event& event);
	// Verarbeitung
	void resetGame();
	void updateCollision();
	void updateFruit();
	void updateSnake();
	// Ausgabe
	void renderArena(sf::RenderWindow& window);
	void renderFruit(sf::RenderWindow& window);
	void renderSnake(sf::RenderWindow& window);

	
	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif

