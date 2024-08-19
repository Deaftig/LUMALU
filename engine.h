/* LUMALU
*/
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

class Engine {
public:
    sf::RenderWindow window;
    sf::Event event;

    Engine();
    void run();

private:
    void initWindow();
};

#endif
