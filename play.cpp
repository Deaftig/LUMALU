/*
LOGIC FOR GAMEPLAY
-NEEDS A SCREEN, WHERE THE PLAYER CAN ENTER HIS/HER NAME
-NEEDS TO DO EVERYTHING FOR THE SNAKE GAME
-NEEDS A GAME-OVER SCREEN WHERE POINTS ARE DISPLAYED
-NEEDS TO SAVE THE NAME AND POINTS INTO scoreboard.txt
*/

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>

// Header-Dateien
#include "globals.h"
#include "play.h"

void Play::handleInput(sf::RenderWindow& window) {
    // Eingabeverwaltung für das Spiel
}

void Play::update() {
    // Logik zum Aktualisieren des Spiels
}

void Play::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);

    // Spiel-Elemente zeichnen

    window.display();
}
