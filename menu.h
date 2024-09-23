// Header Guards: Verhindert mehrfaches Einbinden dieser Datei
#ifndef MENU
#define MENU

// Bibliotheken: Einbinden der SFML-Bibliothek f�r Grafikoperationen
#include <SFML/Graphics.hpp>

// Klasse Menu: Verwaltert das Hauptmen� des Spiels
class Menu {
public:
    // Konstruktor: Initialisiert ein Menu-Objekt
    Menu();

    // EVA-Prinzip (Eingabe, Verarbeitung, Ausgabe):
    int input(sf::Event& event);     // Verarbeitet Benutzereingaben
    void update();                  // Aktualisiert den Zustand des Men�s
    void render(sf::RenderWindow& window); // Zeichnet das Men� auf das Fenster

private:
    // Instanzen: Objekte zur Darstellung des Men�s
    sf::Font font;                  // Schriftart f�r die Texte im Men�
    sf::Text titleText;             // Text f�r den Titel des Men�s
    sf::Text startText;             // Text f�r den Start-Button
    sf::Text highscoreText;         // Text f�r den Highscore-Button
    sf::Text quitText;              // Text f�r den Beenden-Button
    sf::Text helpText;              // Text f�r die Hilfestellung

    // Variablen: Zum Verwalten des aktuellen Men�auswahlpunkts
    int selectedMenuItem = 1;       // Index des aktuell ausgew�hlten Men�punktes

    // Funktionen: Hilfsfunktionen zur Initialisierung und Aktualisierung der Men�texte
    void updateTextColors();         // Aktualisiert die Farben der Men�texte basierend auf der Auswahl
    void initTextStrings();          // Initialisiert die Textinhalte der Men�elemente
    void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position); // Initialisiert einen zentrierten Text
};

#endif // Ende der Header Guards
