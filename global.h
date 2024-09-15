// Header Guards: Verhindert mehrfaches Einbinden dieser Datei
#ifndef GLOBAL
#define GLOBAL

// SFML-Bibliotheken: Einbinden der SFML-Bibliothek für Grafikfunktionen
#include <SFML/Graphics.hpp>

// Namespace "gb" für besserer Organisation und Übersichtlichkeit
namespace gb {
    // Konstanten: Definiert Farben und andere feste Werte für das Spiel
    
    // Farben: Definitionen für verschiedene Farbwerte, die im Spiel verwendet werden
    const sf::Color colTextOff(200, 200, 200);   // Farbe für deaktivierten Text
    const sf::Color colTextOn(255, 255, 255);    // Farbe für aktivierten Text
    const sf::Color colFruit(202, 83, 51);       // Farbe der Frucht
    const sf::Color colSnake(94, 115, 223);      // Farbe der Schlange
    const sf::Color colBackground(51, 70, 118);  // Hintergrundfarbe des Spiels
    const sf::Color colArena1(188, 206, 244);    // Farbe für Arena-Muster (erste Farbe)
    const sf::Color colArena2(173, 195, 239);    // Farbe für Arena-Muster (zweite Farbe)

    // Fenstergröße: Definition der Größe des Spiel-Fensters
    const int winWidth = 600;  // Breite des Fensters
    const int winHeight = 600; // Höhe des Fensters

    // Arena, Frucht, Schlange: Definitionen für die Arena und andere Spiel-Elemente
    const int blockSize = 30;               // Größe eines Blocks in der Arena
    const int arenaWidth = 18;              // Breite der Arena in Blockeinheiten
    const int arenaHeight = 16;             // Höhe der Arena in Blockeinheiten
    const int xOffset = ((gb::winWidth - (gb::arenaWidth * gb::blockSize)) / 2); // Horizontale Versatzberechnung
    const int yOffset = (gb::winHeight - (gb::arenaHeight * gb::blockSize) - 10); // Vertikale Versatzberechnung (inkl. zusätzlicher Margin)

    // Funktionen: Hilfsfunktionen zur Überprüfung von Tasteneingaben
    
    // Überprüft, ob eine beliebige Taste gedrückt wurde
    inline bool pressedAnyKey(sf::Event& event) {
        return event.type == sf::Event::KeyPressed;
    }

    // Überprüft, ob die Enter-Taste gedrückt wurde
    inline bool pressedEnter(sf::Event& event) {
        return event.key.code == sf::Keyboard::Enter;
    }

    // Überprüft, ob die Escape-Taste gedrückt wurde
    inline bool pressedEscape(sf::Event& event) {
        return event.key.code == sf::Keyboard::Escape;
    }

    // Überprüft, ob die W-Taste gedrückt wurde
    inline bool pressedW(sf::Event& event) {
        return event.key.code == sf::Keyboard::W;
    }

    // Überprüft, ob die A-Taste gedrückt wurde
    inline bool pressedA(sf::Event& event) {
        return event.key.code == sf::Keyboard::A;
    }

    // Überprüft, ob die S-Taste gedrückt wurde
    inline bool pressedS(sf::Event& event) {
        return event.key.code == sf::Keyboard::S;
    }

    // Überprüft, ob die D-Taste gedrückt wurde
    inline bool pressedD(sf::Event& event) {
        return event.key.code == sf::Keyboard::D;
    }
};

#endif // Ende der Header Guards

/*
[global.h] beinhaltet globale Deklarationen und Funktionen. Das Definieren dieser
zentralen Definitionen im namespace "gb" ermöglicht es, den Gesamtcode übersichtlicher
zu gestalten.
*/
