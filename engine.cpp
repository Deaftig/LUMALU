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

            /*
            int action ist der Integer - Rückgabewert der Funktion "handleInput"
            0 = Fenster schließen
            1 = Wechsel in den Modus Spiel
            2 = Wechsel in den Modus Bestenliste
            3 = Wechsel in den Modus Menü
            */
            int action = 0;
            switch (currentState)
            {
            case STATE_MENU:
                action = menu.handleInput(event);
                if (action == 1) {currentState = STATE_PLAY;}

                // Auswahl Menüpunkt Bestenliste
                else if (action == 2) {currentState = STATE_SCOREBOARD;}

                else if (action == 0) {window.close();}
                menu.render(window);
                break;

            case STATE_PLAY:
                action = game.handleInput(event);
                if (action == 3) {currentState = STATE_MENU;}
                game.render(window);
                break;

            case STATE_SCOREBOARD:
                action = scoreboard.handleInput(event);
                if (action == 3) {currentState = STATE_MENU;}
                scoreboard.render(window);
                break;
            }
        }
    }
}



void Engine::initWindow()
{
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SFML Game", sf::Style::None);
}
