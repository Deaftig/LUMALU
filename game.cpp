#include "game.h"
#include "globals.h"

Game::Game()
{
}

void Game::render(sf::RenderWindow& window)
{
    window.clear(gb::colArena2);
    window.display();
}

int Game::handleInput(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        return 3;
    }
}
