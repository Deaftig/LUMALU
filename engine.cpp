#include "engine.h"

#include "globals.h"

// PUBLIC
Engine::Engine() {
   window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}

// IPO
void Engine::run() {
    while (window.isOpen()) {

        handleInput();
        update(deltaTime);
        render();
    }
}


void Engine::handleInput() {
        // Ereignisverarbeitung
        while (window.pollEvent(event)) {
            int action = 0; //Zurücksetzen des Integer
            switch (currentState) {
            case STATE_MENU:
                action = menu.handleInput(event);
                if (action == 1) { currentState = STATE_PLAY; }
                else if (action == 2) { currentState = STATE_SCOREBOARD; }
                else if (action == 0) { window.close(); }
                break;

            case STATE_PLAY:
                action = game.handleInput(event);
                if (action == 3) { currentState = STATE_MENU; }
                break;

            case STATE_SCOREBOARD:
                action = scoreboard.handleInput(event);
                if (action == 3) { currentState = STATE_MENU; }
                break;
            }
        }
    }

void Engine::update(float deltaTime) {
    switch (currentState) {
    case STATE_MENU:
        menu.update(deltaTime);
        break;
    case STATE_PLAY:
        game.update(deltaTime);
        break;
    case STATE_SCOREBOARD:
        scoreboard.update(deltaTime);
        break;
    }
}

void Engine::render() {
        window.clear(gb::colBackground);
        switch (currentState) {
        case STATE_MENU:
            menu.render(window);
            break;
        case STATE_PLAY:
            game.render(window);
            break;
        case STATE_SCOREBOARD:
            scoreboard.render(window);
            break;
        }
        window.display();  
}