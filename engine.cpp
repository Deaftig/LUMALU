#include "engine.h"
#include "menu.h"
#include "play.h"
#include "scoreboard.h"
#include "globals.h"

void Engine::run() {
    sf::RenderWindow window(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game",sf::Style::None);

    enum State { STATE_MENU, STATE_PLAY, STATE_SCOREBOARD };
    State currentState = STATE_MENU;

    Menu menu;
    Play play;
    Scoreboard scoreboard;

    while (window.isOpen()) {
        switch (currentState) {
        case STATE_MENU:
            menu.handleInput(window);
            menu.update();
            menu.render(window);
            break;
        case STATE_PLAY:
            play.handleInput(window);
            play.update();
            play.render(window);
            break;
        case STATE_SCOREBOARD:
            scoreboard.handleInput(window);
            scoreboard.update();
            scoreboard.render(window);
            break;
        }
    }
}


