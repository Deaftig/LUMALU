#ifndef MENU_H
#define MENU_H

// SFML-Bibliothek
#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu();
    void handleInput(sf::RenderWindow& window);
    void update();
    void render(sf::RenderWindow& window);

private:

};

#endif
