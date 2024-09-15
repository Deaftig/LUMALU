// Header-Dateien: Importieren der notwendigen Header-Dateien f�r die Engine-Klasse
#include "engine.h"   // Header-Datei f�r die Engine-Klasse
#include "global.h"   // Header-Datei f�r globale Konstanten und Variablen

// Konstruktor der Engine-Klasse: Initialisiert die Engine
Engine::Engine() {
    initWindow();                // Fenster initialisieren
    game.setScoreboard(scoreboard); // Setzt das Punktesystem f�r das Spiel
}

// Hauptschleife der Engine: F�hrt das Spiel aus, solange das Fenster ge�ffnet ist
void Engine::run() {
    while (window.isOpen()) {   // Solange das Fenster ge�ffnet ist
        time = clock.getElapsedTime(); // Zeit seit dem R�cksetzen holen
        if (time.asMilliseconds() >= 16.67f) { // Vergangene Zeit >= 16,67 ms (60Hz) Schleife starten
            input();        // Eingaben verarbeiten
            update();       // Spielzustand aktualisieren
            render();       // Alles auf dem Fenster rendern
            clock.restart(); // Uhr zur�cksetzen
        }
    }
}

// Eingaben verarbeiten: Reagiert auf Benutzeraktionen basierend auf dem aktuellen Zustand
void Engine::input() {
    while (window.pollEvent(event)) { // Alle Ereignisse abfragen
        int action = 0;               // Zur�cksetzen der Variable "action"
        switch (currentState) {       // Reagiere je nach aktuellem Zustand
        case STATE_MENU:
            action = menu.input(event); // Eingaben des Men�s verarbeiten
            if (action == 1) { currentState = STATE_PLAY; } // Wechsel zum Spiel-Zustand
            else if (action == 2) { currentState = STATE_SCOREBOARD; } // Wechsel zur Bestenliste
            else if (action == 0) { window.close(); } // Schlie�t das Fenster
            break;
        case STATE_PLAY:
            action = game.input(event); // Eingaben des Spiels verarbeiten
            if (action == 3) { currentState = STATE_MENU; } // Wechsel zum Men�-Zustand
            break;
        case STATE_SCOREBOARD:
            action = scoreboard.input(event); // Eingaben der Bestenliste verarbeiten
            if (action == 3) { currentState = STATE_MENU; } // Wechsel zum Men�-Zustand
            break;
        }
    }
}

// Spielzustand aktualisieren: Aktualisiert den Zustand des Spiels basierend auf dem aktuellen Zustand
void Engine::update() {
    switch (currentState) { // Reagiere je nach aktuellem Zustand
    case STATE_MENU:
        menu.update(); // Men� aktualisieren
        break;
    case STATE_PLAY:
        game.update(); // Spiel aktualisieren
        break;
    case STATE_SCOREBOARD:
        scoreboard.update(); // Bestenliste aktualisieren
        break;
    }
}

// Rendern: Zeichnet den aktuellen Zustand auf dem Fenster
void Engine::render() {
    window.clear(gb::colBackground); // Fenster mit Hintergrundfarbe f�llen
    switch (currentState) { // Reagiere je nach aktuellem Zustand
    case STATE_MENU:
        menu.render(window); // Men� rendern
        break;
    case STATE_PLAY:
        game.render(window); // Spiel rendern
        break;
    case STATE_SCOREBOARD:
        scoreboard.render(window); // Bestenliste rendern
        break;
    }
    window.display(); // Fensterinhalt aktualisieren
}

// Fenster initialisieren: Erzeugt das Hauptfenster des Spiels
void Engine::initWindow() {
    /*Erstelle ein Fenster mit der vordefinierten Gr��e aus "global.h", nenne es "SNAKE von LUMALU",
     setze keinen Stil (keine Taskbar, Vollbildschirm, ver�nderbare Gr��e, etc.)*/
    window.create(sf::VideoMode(gb::winWidth, gb::winHeight), "SNAKE von LUMALU", sf::Style::None);
}

/*
[engine.cpp] beinhaltet das Management der einzelnen Zust�nde (Men�, Spielumgebung, Scoreboard) und
das Erstellen des Fensters, in welchem das Spiel dargestellt wird.
Die Hauptschleife "Engine::Run" �berpr�ft vor jedem Durchlauf, ob das Fenster noch ge�ffnet ist, danach wird �berpr�ft,
ob min. 16,67ms vergangen sind. Sollten beide �berpr�fungen positiv ausfallen, wird eine neue Schleife gestartet.
Zus�tzlich wird anhand der Switch-Statements entschieden, welcher Zustand derzeit aktiv ist.
*/