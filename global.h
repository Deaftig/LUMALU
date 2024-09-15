// Header Guards: Verhindert mehrfaches Einbinden dieser Datei
#ifndef GLOBAL
#define GLOBAL

// SFML-Bibliotheken: Einbinden der SFML-Bibliothek f�r Grafikfunktionen
#include <SFML/Graphics.hpp>

// Namespace "gb" f�r besserer Organisation und �bersichtlichkeit
namespace gb {
    // Konstanten: Definiert Farben und andere feste Werte f�r das Spiel
    
    // Farben: Definitionen f�r verschiedene Farbwerte, die im Spiel verwendet werden
    const sf::Color colTextOff(200, 200, 200);   // Farbe f�r deaktivierten Text
    const sf::Color colTextOn(255, 255, 255);    // Farbe f�r aktivierten Text
    const sf::Color colFruit(202, 83, 51);       // Farbe der Frucht
    const sf::Color colSnake(94, 115, 223);      // Farbe der Schlange
    const sf::Color colBackground(51, 70, 118);  // Hintergrundfarbe des Spiels
    const sf::Color colArena1(188, 206, 244);    // Farbe f�r Arena-Muster (erste Farbe)
    const sf::Color colArena2(173, 195, 239);    // Farbe f�r Arena-Muster (zweite Farbe)

    // Fenstergr��e: Definition der Gr��e des Spiel-Fensters
    const int winWidth = 600;  // Breite des Fensters
    const int winHeight = 600; // H�he des Fensters

    // Arena, Frucht, Schlange: Definitionen f�r die Arena und andere Spiel-Elemente
    const int blockSize = 30;               // Gr��e eines Blocks in der Arena
    const int arenaWidth = 18;              // Breite der Arena in Blockeinheiten
    const int arenaHeight = 16;             // H�he der Arena in Blockeinheiten
    const int xOffset = ((gb::winWidth - (gb::arenaWidth * gb::blockSize)) / 2); // Horizontale Versatzberechnung
    const int yOffset = (gb::winHeight - (gb::arenaHeight * gb::blockSize) - 10); // Vertikale Versatzberechnung (inkl. zus�tzlicher Margin)

    // Funktionen: Hilfsfunktionen zur �berpr�fung von Tasteneingaben
    
    // �berpr�ft, ob eine beliebige Taste gedr�ckt wurde
    inline bool pressedAnyKey(sf::Event& event) {
        return event.type == sf::Event::KeyPressed;
    }

    // �berpr�ft, ob die Enter-Taste gedr�ckt wurde
    inline bool pressedEnter(sf::Event& event) {
        return event.key.code == sf::Keyboard::Enter;
    }

    // �berpr�ft, ob die Escape-Taste gedr�ckt wurde
    inline bool pressedEscape(sf::Event& event) {
        return event.key.code == sf::Keyboard::Escape;
    }

    // �berpr�ft, ob die W-Taste gedr�ckt wurde
    inline bool pressedW(sf::Event& event) {
        return event.key.code == sf::Keyboard::W;
    }

    // �berpr�ft, ob die A-Taste gedr�ckt wurde
    inline bool pressedA(sf::Event& event) {
        return event.key.code == sf::Keyboard::A;
    }

    // �berpr�ft, ob die S-Taste gedr�ckt wurde
    inline bool pressedS(sf::Event& event) {
        return event.key.code == sf::Keyboard::S;
    }

    // �berpr�ft, ob die D-Taste gedr�ckt wurde
    inline bool pressedD(sf::Event& event) {
        return event.key.code == sf::Keyboard::D;
    }
};

#endif // Ende der Header Guards

/*
[global.h] beinhaltet globale Deklarationen und Funktionen. Das Definieren dieser
zentralen Definitionen im namespace "gb" erm�glicht es, den Gesamtcode �bersichtlicher
zu gestalten.
*/
