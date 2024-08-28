#include "engine.h"

#include "globals.h"

Engine::Engine()
{
    initWindow();
}

void Engine::run() {

    while (window.isOpen())
    {
        handleInput();
        update();
        render();
    }
}

void Engine::handleInput() {
        // Ereignisverarbeitung
        while (window.pollEvent(event))
        {
            int action = 0; //Zurücksetzen des Integer
            switch (currentState)
            {
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

void Engine::render(){
        window.clear(gb::colBackground);
        switch (currentState)
        {
        case STATE_MENU:
            menu.render(window);
            break;
        case STATE_PLAY:
            game.update();
            game.render(window);
            break;
        case STATE_SCOREBOARD:
            scoreboard.render(window);
            break;
        }
        window.display();  
}

void Engine::update() {
    switch (currentState)
    {
    case STATE_MENU:
        break;
    case STATE_PLAY:
        game.update();
        break;
    case STATE_SCOREBOARD:
        break;
    }
}

void Engine::initWindow()
{
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}
