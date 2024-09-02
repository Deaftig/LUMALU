// Header Guards
#ifndef ENGINE
#define ENGINE

// Header-Dateien
#include "menu.h"
#include "game.h"
#include "scoreboard.h"

// Bibliotheken
#include <SFML/Graphics.hpp>
#include <iostream>

// Klasse Engine
class Engine {
public:
    // Instanzen
    Menu menu;
    Game game;
    Scoreboard scoreboard;
    sf::RenderWindow window;
    sf::Event event;
    sf::Font font;
    sf::Clock clock;
    sf::Time time;

    // Variablen
    enum State { STATE_MENU, STATE_PLAY, STATE_SCOREBOARD};
    State currentState = STATE_MENU;

    // Constructor
    Engine();

    // Hauptschleife
    void run();   

    // EVA
    void input();
    void update();
    void render();

    // Funktionen
    void initWindow();
};
#endif