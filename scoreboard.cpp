/* LUMALU
*/
#include "scoreboard.h"
#include "globals.h"

Scoreboard::Scoreboard()
{
}

void Scoreboard::render(sf::RenderWindow& window)
{
    window.clear(gb::colArena1);
    window.display();
}

int Scoreboard::handleInput(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        return 3;
    }
}
