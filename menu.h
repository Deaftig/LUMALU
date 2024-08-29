/* LUMALU
*/
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>



class Menu {
public:
    Menu();
    int handleInput(sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;
    sf::Text highscoreText;
    sf::Text quitText;
    sf::Text helpText;
    int selectedMenuItem;



    void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position);
    void updateTextColors();
};

#endif
