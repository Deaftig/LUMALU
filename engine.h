// Header Guards: Verhindert mehrfaches Einbinden der Header-Datei w�hrend der Kompilierung
#ifndef ENGINE
#define ENGINE

// Header-Dateien: Importieren von ben�tigten Modulen und anderen Header-Dateien
#include "menu.h"         // Enth�lt die Deklarationen f�r das Men�
#include "game.h"         // Enth�lt die Deklarationen f�r die Spiel-Logik
#include "scoreboard.h"   // Enth�lt die Deklarationen f�r ie Bestenliste

// Bibliotheken: Externe Bibliotheken f�r Grafik, Fenster-Management und Konsolenausgabe
#include <SFML/Graphics.hpp>  // SFML f�r Grafiken (RenderWindow, etc.)
#include <SFML/Window.hpp>    // SFML f�r Fenster und Benutzer-Events

// Definition der Klasse Engine, die die Hauptlogik des Programms enth�lt
class Engine {
public:
    // Instanzen: Objekte anderer Klassen, die in der Engine verwendet werden
    Menu menu;               // Objekt f�r das Hauptmen�
    Game game;               // Objekt f�r die Spiellogik
    Scoreboard scoreboard;   // Objekt f�r die Anzeigetafel

    // SFML-Objekte f�r die Verwaltung von Fenstern und Ereignissen
    sf::RenderWindow window; // Hauptfenster, in dem das Spiel dargestellt wird
    sf::Event event;         // Verwaltung von Benutzerereignissen (Tastatureingaben, Maus, etc.)
    sf::Font font;           // Schriftart f�r Textelemente im Spiel
    sf::Clock clock;         // Uhr f�r das Steuern der Hauptschleife
    sf::Time time;           // Zeitvariable f�r das Steuern der Hauptschleife

    // Spielzust�nde: Enum zur Verwaltung der verschiedenen Zust�nde des Spiels
    enum State {
        STATE_MENU,          // Men�
        STATE_PLAY,          // Spiel
        STATE_SCOREBOARD,    // Bestenliste
    };
    State currentState = STATE_MENU; // Aktueller Zustand, initialisiert mit dem Men�

    // Konstruktor: Initialisiert ein Engine-Objekt
    Engine();

    // Hauptschleife des Spiels: Hier wird die Logik wiederholt, bis das Programm beendet wird
    void run();

    // EVA-Prinzip (Eingabe, Verarbeitung, Ausgabe):
    void input();    // Funktion zur Verarbeitung von Eingaben
    void update();   // Funktion zur Aktualisierung der Spielzust�nde
    void render();   // Funktion zur Darstellung des aktuellen Zustands im Fenster

    // Initialisierung des Fensters
    void initWindow();
};
#endif // Ende der Header Guards

/*
[engine.h] enth�lt die Deklarationen f�r die Engine-Klasse, die die Hauptlogik des Programms verwaltet.
Die Header Guards am Anfang verhindern, dass diese Header-Datei mehrfach in den Kompilierungsprozess
eingebunden wird.

Das Einbinden von "menu.h", "game.h" und "scoreboard.h" erm�glicht der Engine, auf das Hauptmen�,
die Spiel-Logik und die Bestenliste zuzugreifen. Die SFML-Bibliotheken werden verwendet, um
Grafiken, Fenster und Ereignisse zu verwalten.
*/
