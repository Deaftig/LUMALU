#ifndef ENGINE_H
#define ENGINE_H

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>


class Engine {

public:
    Engine();      // ??? How is this being called? I'm only calling "engine.run" in "int main"
    void run();

private:        // ??? Private functions, only available to the class Engine, right?
    sf::RenderWindow window;        // ??? Still not entirely sure of the syntax here
    sf::Event event;                // ??? Same thing here. Why can't I just use sf::Event everywhere?

    void initWindow();              // just a function to initiate the window
};

#endif
