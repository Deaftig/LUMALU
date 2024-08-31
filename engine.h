// Header Guards
#ifndef ENGINE
#define ENGINE

// Header-Dateien
#include "menu.h"
#include "game.h"
#include "scoreboard.h"

// SFML
#include <SFML/Graphics.hpp>

// Engine
class Engine {
public:
    Menu menu;
    Game game;
    Scoreboard scoreboard;

    // SFML
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    sf::Time time;

    // Funktionen
    Engine();
    void run();             
    void handleInput();
    void update();
    void render();

private:
    enum State { STATE_MENU, STATE_PLAY, STATE_SCOREBOARD };
    State currentState = STATE_MENU;
};

#endif
