/* LUMALU
*/
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>

class Engine {
public:
    Menu menu;
    Game game;
    Scoreboard scoreboard;

    sf::RenderWindow window;
    sf::Event event;

    Engine();
    void run();

private:
    enum State { STATE_MENU, STATE_PLAY, STATE_SCOREBOARD };
    State currentState = STATE_MENU;

    void initWindow();
    void handleInput();
    void update();
    void render();
};

#endif
