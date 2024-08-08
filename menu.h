#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu();  // Konstruktor zum Laden der Schriftart und Initialisieren des Texts
    void handleInput(sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);

private:
    sf::Font font;  // Schriftart für das Menü
    sf::Text titleText;
    sf::Text startText;
    sf::Text highscoreText;
    sf::Text quitText;
    int selectedItem;  // Index des aktuell ausgewählten Menüpunktes

    void initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
    void updateTextColors();  // Hilfsmethode zur Aktualisierung der Farben der Menüpunkte
};

#endif
