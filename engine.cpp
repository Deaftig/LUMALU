// Header-Dateien
#include "engine.h"
#include "globals.h"

Engine::Engine() {
    initWindow();
    std::cout << "Engine initialisert \n"; //DEBUG
}

void Engine::run() {
    while (window.isOpen()) {
        time = clock.getElapsedTime();
        if (time.asMilliseconds() >= 16.67f) {
            input();
            update();
            render();
            clock.restart();
        }
    }
}

void Engine::input() {
    while (window.pollEvent(event)) {
        int action = 0;
        switch (currentState) {
        case STATE_MENU:
            action = menu.input(event);
            if (action == 1) { currentState = STATE_PLAY; }
            else if (action == 2) { currentState = STATE_SCOREBOARD; }
            else if (action == 0) { window.close(); }
            break;
        case STATE_PLAY:
            action = game.input(event);
            if (action == 3) { currentState = STATE_MENU; }
            break;
        case STATE_SCOREBOARD:
            action = scoreboard.input(event);
            if (action == 3) { currentState = STATE_MENU; }
            break;
        }
    }
}

void Engine::update() {
    switch (currentState) {
    case STATE_MENU:
        menu.update();
        break;
    case STATE_PLAY:
        game.update();
        break;
    case STATE_SCOREBOARD:
        scoreboard.update();
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

void Engine::initWindow() {
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}
