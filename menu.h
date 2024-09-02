// Header Guards
#ifndef MENU
#define MENU

// Bibliotheken
#include <SFML/Graphics.hpp>

// Klasse Menu
class Menu {
public:
    // Constructor
    Menu();

    // EVA
    int input(sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

private:
    // Instanzen
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text highscoreText;
    sf::Text quitText;
    sf::Text helpText;

    // Variablen
    int selectedMenuItem = 0;

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