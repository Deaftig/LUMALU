#include "engine.h"
#include "menu.h"
#include "game.h"
#include "scoreboard.h"
#include "globals.h"

Engine::Engine()
{
    initWindow();
}

void Engine::run() {
    enum State { STATE_MENU, STATE_PLAY, STATE_SCOREBOARD };
    State currentState = STATE_MENU;

    Menu menu;
    Game game;
    Scoreboard scoreboard;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            int action = 0;
            switch (currentState) {
            case STATE_MENU:
                menu.handleInput(event);
                menu.render(window);
                break;
            case STATE_PLAY:
                break;
            case STATE_SCOREBOARD:
                break;
            }

        }
        window.display();
    }
}


void Engine::initWindow()
{
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}
