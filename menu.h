// Header Guards: Verhindert mehrfaches Einbinden dieser Datei
#ifndef MENU
#define MENU

// Bibliotheken: Einbinden der SFML-Bibliothek für Grafikoperationen
#include <SFML/Graphics.hpp>

// Klasse Menu: Verwaltert das Hauptmenü des Spiels
class Menu {
public:
    // Konstruktor: Initialisiert ein Menu-Objekt
    Menu();

    // EVA-Prinzip (Eingabe, Verarbeitung, Ausgabe):
    int input(sf::Event& event);     // Verarbeitet Benutzereingaben
    void update();                  // Aktualisiert den Zustand des Menüs
    void render(sf::RenderWindow& window); // Zeichnet das Menü auf das Fenster

private:
    // Instanzen: Objekte zur Darstellung des Menüs
    sf::Font font;                  // Schriftart für die Texte im Menü
    sf::Text titleText;             // Text für den Titel des Menüs
    sf::Text startText;             // Text für den Start-Button
    sf::Text highscoreText;         // Text für den Highscore-Button
    sf::Text quitText;              // Text für den Beenden-Button
    sf::Text helpText;              // Text für die Hilfestellung

    // Variablen: Zum Verwalten des aktuellen Menüauswahlpunkts
    int selectedMenuItem = 1;       // Index des aktuell ausgewählten Menüpunktes

    // Funktionen: Hilfsfunktionen zur Initialisierung und Aktualisierung der Menütexte
    void updateTextColors();         // Aktualisiert die Farben der Menütexte basierend auf der Auswahl
    void initTextStrings();          // Initialisiert die Textinhalte der Menüelemente
    void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position); // Initialisiert einen zentrierten Text
};

#endif // Ende der Header Guards
