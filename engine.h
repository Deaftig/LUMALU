#ifndef ENGINE_H
#define ENGINE_H

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>


class Engine {

public:
    Engine();
    void run();

private:
    sf::RenderWindow window;
    void initWindow();
};

#endif
