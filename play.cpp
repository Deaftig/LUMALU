#include <SFML/Graphics.hpp>
#include "globals.h"
#include "play.h"

void Play::handleInput(sf::RenderWindow& window) {
    // Eingabeverwaltung f�r das Spiel
}

void Play::update() {
    // Logik zum Aktualisieren des Spiels
}

void Play::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);

    // Spiel-Elemente zeichnen

    window.display();
}
