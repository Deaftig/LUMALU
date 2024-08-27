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
        // Ereignisverarbeitung
        while (window.pollEvent(event))
        {
            int action = 0; //Zurücksetzen des Integer
            switch (currentState)
            {
            case STATE_MENU:
                action = menu.handleInput(event);
                if (action == 1)        { currentState = STATE_PLAY; }
                else if (action == 2)   { currentState = STATE_SCOREBOARD; }
                else if (action == 0)   { window.close(); }
                break;

            case STATE_PLAY:
                action = game.handleInput(event);
                if (action == 3)        { currentState = STATE_MENU; }
                break;

            case STATE_SCOREBOARD:
                action = scoreboard.handleInput(event);
                if (action == 3)        { currentState = STATE_MENU; }
                break;
            }
        }

        // Rendern des aktuellen Zustands
        window.clear(gb::colBackground);  // Hintergrund aktualisieren
        switch (currentState)
        {
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
        window.display();  // Das Fenster nach dem Zeichnen anzeigen
    }
}

void Engine::initWindow()
{
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}
