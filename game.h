// Header Guards: Verhindert das mehrfache Einbinden der Header-Datei
#ifndef GAME
#define GAME

// Header-Dateien: Inkludiert die Scoreboard-Klasse
#include "scoreboard.h"

// Bibliotheken: Einbinden der SFML-Bibliothek und Vektoren
#include <SFML/Graphics.hpp>
#include <vector>

// Klasse Game: Verwaltet die Spiellogik, wie Schlange, Frucht und Punkte
class Game {
public:
    // Constructor: Initialisiert die Spiellogik
    Game();
    void setScoreboard(Scoreboard& inScoreboard); // Setzt die Verkn�pfung zum Scoreboard

    // EVA-Prinzip (Eingabe, Verarbeitung, Ausgabe)
    int input(sf::Event& event);               // Verarbeitet die Benutzereingaben
    void update();                             // Aktualisiert das Spiel (z.B. Bewegung der Schlange)
    void render(sf::RenderWindow& window);     // Zeichnet das Spielfeld, die Schlange und die Frucht

private:
    // Instanzen: Objekte zur Verwaltung des Spiels
    Scoreboard* scoreboard = nullptr;           // Zeiger auf das Scoreboard-Objekt
    sf::Font font;                              // Schriftart f�r Textanzeigen
    sf::Text finalText;                         // Text f�r das Spielende
    sf::Text activeScoreText;                   // Text f�r die aktuelle Punktzahl
    sf::Text finalScoreText;                    // Text f�r die Endpunktzahl
    sf::Text nameText;                          // Text f�r den Spielernamen
    sf::Text helpText;                          // Text f�r die Hilfestellung
    sf::CircleShape fruit;                      // Form f�r die Frucht
    sf::Clock moveClock;                        // Uhr zur Messung der Zeit f�r die Schlangenbewegung
    sf::Time moveInterval;                      // Zeitintervall f�r die Bewegung der Schlange
    std::vector<sf::Vector2i> snake;            // Vektor zur Speicherung der Position der Schlange
    sf::Vector2i direction;                     // Bewegungsrichtung der Schlange
    std::string playerName;                     // Name des Spielers

    // Variablen: Zustandsvariablen des Spiels
    bool fruitActive = false;                   // Gibt an, ob eine Frucht aktiv auf dem Spielfeld ist
    bool snakeActive = false;                   // Gibt an, ob die Schlange sich aktiv bewegt
    bool gameOver = false;                      // Gibt an, ob das Spiel vorbei ist
    int playerScore = 0;                        // Punktzahl des Spielers
    bool growSnake = false;                     // Gibt an, ob die Schlange wachsen soll (nach dem Fressen)

    // Eingabe: Funktionen zur Verarbeitung der Eingaben
    int processState(sf::Event& event);         // Verarbeitet Eingaben w�hrend des Spiels
    int processState_gameOver(sf::Event& event);// Verarbeitet Eingaben im Spielende-Zustand

    // Verarbeitung: Funktionen zur Aktualisierung des Spiels
    void updateCollision();                     // �berpr�ft Kollisionen (z.B. Schlange und Wand)
    void updateFruit();                         // Aktualisiert die Position und den Zustand der Frucht
    void updateSnake();                         // Aktualisiert die Bewegung der Schlange

    // Ausgabe: Funktionen zur Darstellung des Spiels
    void renderArena(sf::RenderWindow& window); // Zeichnet die Spielfeldarena
    void renderFruit(sf::RenderWindow& window); // Zeichnet die Frucht
    void renderSnake(sf::RenderWindow& window); // Zeichnet die Schlange

    // Funktionen: Hilfsfunktionen zur Verwaltung des Spiels
    void resetGame();                           // Setzt das Spiel zur�ck (z.B. nach Spielende)
    void spawnFruit();                          // Erzeugt eine neue Frucht auf dem Spielfeld
    void spawnSnake();                          // Setzt die Schlange auf die Startposition
    void scoreboardEntry();                     // F�gt den aktuellen Spielstand in die Bestenliste ein
    sf::Vector2f getScreenPosition(float x, float y); // Wandelt Spielfeldkoordinaten in Bildschirmkoordinaten um
    void getName(sf::Event& event);
    void initTextStrings();                     // Initialisiert die Textobjekte (z.B. Punktestand, Spielende)
    void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position); // Zentriert und formatiert Text
};
#endif // Ende der Header Guards

