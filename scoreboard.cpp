#include <SFML/Graphics.hpp>
#include "globals.h"
#include "scoreboard.h"

void Scoreboard::handleInput(sf::RenderWindow& window) {
    // Eingabeverwaltung f�r das Scoreboard
}

void Scoreboard::update() {
    // Logik zum Aktualisieren des Scoreboards
}

void Scoreboard::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);

    // Scoreboard-Elemente zeichnen

    window.display();
}
