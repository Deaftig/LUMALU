// Header Guards: Verhindert mehrfaches Einbinden der Header-Datei während der Kompilierung
#ifndef ENGINE
#define ENGINE

// Header-Dateien: Importieren von benötigten Modulen und anderen Header-Dateien
#include "menu.h"         // Enthält die Deklarationen für das Menü
#include "game.h"         // Enthält die Deklarationen für die Spiel-Logik
#include "scoreboard.h"   // Enthält die Deklarationen für ie Bestenliste

// Bibliotheken: Externe Bibliotheken für Grafik, Fenster-Management und Konsolenausgabe
#include <SFML/Graphics.hpp>  // SFML für Grafiken (RenderWindow, etc.)
#include <SFML/Window.hpp>    // SFML für Fenster und Benutzer-Events

// Definition der Klasse Engine, die die Hauptlogik des Programms enthält
class Engine {
public:
    // Instanzen: Objekte anderer Klassen, die in der Engine verwendet werden
    Menu menu;               // Objekt für das Hauptmenü
    Game game;               // Objekt für die Spiellogik
    Scoreboard scoreboard;   // Objekt für die Anzeigetafel

    // SFML-Objekte für die Verwaltung von Fenstern und Ereignissen
    sf::RenderWindow window; // Hauptfenster, in dem das Spiel dargestellt wird
    sf::Event event;         // Verwaltung von Benutzerereignissen (Tastatureingaben, Maus, etc.)
    sf::Font font;           // Schriftart für Textelemente im Spiel
    sf::Clock clock;         // Uhr für das Steuern der Hauptschleife
    sf::Time time;           // Zeitvariable für das Steuern der Hauptschleife

    // Spielzustände: Enum zur Verwaltung der verschiedenen Zustände des Spiels
    enum State {
        STATE_MENU,          // Menü
        STATE_PLAY,          // Spiel
        STATE_SCOREBOARD,    // Bestenliste
    };
    State currentState = STATE_MENU; // Aktueller Zustand, initialisiert mit dem Menü

    // Konstruktor: Initialisiert ein Engine-Objekt
    Engine();

    // Hauptschleife des Spiels: Hier wird die Logik wiederholt, bis das Programm beendet wird
    void run();

    // EVA-Prinzip (Eingabe, Verarbeitung, Ausgabe):
    void input();    // Funktion zur Verarbeitung von Eingaben
    void update();   // Funktion zur Aktualisierung der Spielzustände
    void render();   // Funktion zur Darstellung des aktuellen Zustands im Fenster

    // Initialisierung des Fensters
    void initWindow();
};
#endif // Ende der Header Guards

/*
[engine.h] enthält die Deklarationen für die Engine-Klasse, die die Hauptlogik des Programms verwaltet.
Die Header Guards am Anfang verhindern, dass diese Header-Datei mehrfach in den Kompilierungsprozess
eingebunden wird.

Das Einbinden von "menu.h", "game.h" und "scoreboard.h" ermöglicht der Engine, auf das Hauptmenü,
die Spiel-Logik und die Bestenliste zuzugreifen. Die SFML-Bibliotheken werden verwendet, um
Grafiken, Fenster und Ereignisse zu verwalten.
*/
