// Header-Dateien: Einbinden der Header-Dateien für die Menu-Klasse und globale Konstanten
#include "menu.h"   // Header-Datei für die Menu-Klasse
#include "global.h" // Header-Datei für globale Konstanten und Funktionen

// PUBLIC
// Konstruktor: Initialisiert ein Menu-Objekt und ruft die Funktion zur Initialisierung der Textstrings auf
Menu::Menu() {
    initTextStrings(); // Initialisiert die Texte für das Menü
}

// IPO (Input, Processing, Output)
// Verarbeitet Benutzereingaben und gibt die entsprechende Aktion zurück
int Menu::input(sf::Event& event) {
    if (gb::pressedAnyKey(event)) { // Überprüft, ob eine Taste gedrückt wurde
        if (gb::pressedW(event)) { // Überprüft, ob die W-Taste gedrückt wurde (Nach oben)
            selectedMenuItem = (selectedMenuItem - 1 + 3) % 3; // Auswahl nach oben bewegen
        }
        else if (gb::pressedS(event)) { // Überprüft, ob die S-Taste gedrückt wurde (Nach unten)
            selectedMenuItem = (selectedMenuItem + 1) % 3; // Auswahl nach unten bewegen
        }
        else if (gb::pressedEnter(event)) { // Überprüft, ob die Enter-Taste gedrückt wurde
            if (selectedMenuItem == 0) { return 1; } // START: Gibt 1 zurück, um das Spiel zu starten
            else if (selectedMenuItem == 1) { return 2; } // BESTENLISTE: Gibt 2 zurück, um die Bestenliste anzuzeigen
            else if (selectedMenuItem == 2) { return 0; } // BEENDEN: Gibt 0 zurück, um das Spiel zu beenden
        }
        else if (gb::pressedEscape(event)) { return 0; } // Escape-Taste: Gibt 0 zurück, um das Spiel zu beenden
    }
    return -1; // Keine gültige Eingabe: Gibt -1 zurück
}

// Aktualisiert den Zustand des Menüs (z.B. Textfarben)
void Menu::update() {
    updateTextColors(); // Aktualisiert die Farben der Menütexte basierend auf der Auswahl
}

// Zeichnet das Menü auf dem Fenster
void Menu::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground); // Fenster mit Hintergrundfarbe füllen
    window.draw(titleText);          // Titeltext zeichnen
    window.draw(startText);          // Start-Text zeichnen
    window.draw(highscoreText);      // Highscore-Text zeichnen
    window.draw(quitText);           // Beenden-Text zeichnen
    window.draw(helpText);           // Hilfe-Text zeichnen
}

// --------------------------------------
// PRIVAT
// TEXT
// Aktualisiert die Farben der Menütexte basierend auf dem ausgewählten Menüpunkt
void Menu::updateTextColors() {
    startText.setFillColor(selectedMenuItem == 0 ? gb::colTextOn : gb::colTextOff); // Start-Text hervorheben, wenn ausgewählt
    highscoreText.setFillColor(selectedMenuItem == 1 ? gb::colTextOn : gb::colTextOff); // Highscore-Text hervorheben, wenn ausgewählt
    quitText.setFillColor(selectedMenuItem == 2 ? gb::colTextOn : gb::colTextOff); // Beenden-Text hervorheben, wenn ausgewählt
}

// Initialisiert die Textstrings für das Menü
void Menu::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf"); // Lädt die Schriftart
    // Initialisiert die Texte für das Menü und setzt deren Positionen
    initCenteredText(titleText, "SNAKE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.2));
    initCenteredText(startText, "START", 50, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.4));
    initCenteredText(highscoreText, "BESTENLISTE", 50, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.5));
    initCenteredText(quitText, "BEENDEN", 50, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.6));
    initCenteredText(helpText, "Steuerung mit W,A,S,D, Enter und Escape", 20, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.95));
}

// Initialisiert einen zentrierten Text
void Menu::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(font);                   // Setzt die Schriftart
    text.setString(string);               // Setzt den Textinhalt
    text.setCharacterSize(size);          // Setzt die Schriftgröße
    text.setFillColor(color);             // Setzt die Textfarbe
    text.setPosition(position);           // Setzt die Position des Textes
    sf::FloatRect textBounds = text.getLocalBounds(); // Holt die Grenzen des Textes
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Setzt den Ursprung in die Mitte des Textes
    text.setPosition(position);           // Setzt die Position erneut, um die Zentrierung zu berücksichtigen
}
