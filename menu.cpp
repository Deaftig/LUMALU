// Header-Dateien: Einbinden der Header-Dateien f�r die Menu-Klasse und globale Konstanten
#include "menu.h"   // Header-Datei f�r die Menu-Klasse
#include "global.h" // Header-Datei f�r globale Konstanten und Funktionen

// PUBLIC
// Konstruktor: Initialisiert ein Menu-Objekt und ruft die Funktion zur Initialisierung der Textstrings auf
Menu::Menu() {
    initTextStrings(); // Initialisiert die Texte f�r das Men�
}

// IPO (Input, Processing, Output)
// Verarbeitet Benutzereingaben und gibt die entsprechende Aktion zur�ck
int Menu::input(sf::Event& event) {
    if (gb::pressedAnyKey(event)) { // �berpr�ft, ob eine Taste gedr�ckt wurde
        if (gb::pressedW(event)) { // �berpr�ft, ob die W-Taste gedr�ckt wurde (Nach oben)
            selectedMenuItem = (selectedMenuItem - 1 + 3) % 3; // Auswahl nach oben bewegen
        }
        else if (gb::pressedS(event)) { // �berpr�ft, ob die S-Taste gedr�ckt wurde (Nach unten)
            selectedMenuItem = (selectedMenuItem + 1) % 3; // Auswahl nach unten bewegen
        }
        else if (gb::pressedEnter(event)) { // �berpr�ft, ob die Enter-Taste gedr�ckt wurde
            if (selectedMenuItem == 0) { return 1; } // START: Gibt 1 zur�ck, um das Spiel zu starten
            else if (selectedMenuItem == 1) { return 2; } // BESTENLISTE: Gibt 2 zur�ck, um die Bestenliste anzuzeigen
            else if (selectedMenuItem == 2) { return 0; } // BEENDEN: Gibt 0 zur�ck, um das Spiel zu beenden
        }
        else if (gb::pressedEscape(event)) { return 0; } // Escape-Taste: Gibt 0 zur�ck, um das Spiel zu beenden
    }
    return -1; // Keine g�ltige Eingabe: Gibt -1 zur�ck
}

// Aktualisiert den Zustand des Men�s (z.B. Textfarben)
void Menu::update() {
    updateTextColors(); // Aktualisiert die Farben der Men�texte basierend auf der Auswahl
}

// Zeichnet das Men� auf dem Fenster
void Menu::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground); // Fenster mit Hintergrundfarbe f�llen
    window.draw(titleText);          // Titeltext zeichnen
    window.draw(startText);          // Start-Text zeichnen
    window.draw(highscoreText);      // Highscore-Text zeichnen
    window.draw(quitText);           // Beenden-Text zeichnen
    window.draw(helpText);           // Hilfe-Text zeichnen
}

// --------------------------------------
// PRIVAT
// TEXT
// Aktualisiert die Farben der Men�texte basierend auf dem ausgew�hlten Men�punkt
void Menu::updateTextColors() {
    startText.setFillColor(selectedMenuItem == 0 ? gb::colTextOn : gb::colTextOff); // Start-Text hervorheben, wenn ausgew�hlt
    highscoreText.setFillColor(selectedMenuItem == 1 ? gb::colTextOn : gb::colTextOff); // Highscore-Text hervorheben, wenn ausgew�hlt
    quitText.setFillColor(selectedMenuItem == 2 ? gb::colTextOn : gb::colTextOff); // Beenden-Text hervorheben, wenn ausgew�hlt
}

// Initialisiert die Textstrings f�r das Men�
void Menu::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf"); // L�dt die Schriftart
    // Initialisiert die Texte f�r das Men� und setzt deren Positionen
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
    text.setCharacterSize(size);          // Setzt die Schriftgr��e
    text.setFillColor(color);             // Setzt die Textfarbe
    text.setPosition(position);           // Setzt die Position des Textes
    sf::FloatRect textBounds = text.getLocalBounds(); // Holt die Grenzen des Textes
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Setzt den Ursprung in die Mitte des Textes
    text.setPosition(position);           // Setzt die Position erneut, um die Zentrierung zu ber�cksichtigen
}
