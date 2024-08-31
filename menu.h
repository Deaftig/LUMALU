// Header Guards
#ifndef MENU
#define MENU

// Bibliotheken
#include <SFML/Graphics.hpp>

// Klasse Menu
class Menu {
public:
    // Funktionen
    Menu();
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

    // Funktionen
    void initTextStrings();
    // EVA
    int processState(sf::Event& event);

    void updateTextColors();


    void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
};

#endif
