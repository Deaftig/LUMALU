// Header Guards verhindern, dass die Datei mehrfach inkludiert wird
#ifndef SCOREBOARD
#define SCOREBOARD

// Einbindung der notwendigen Bibliotheken
#include <SFML/Graphics.hpp>  // Für die grafische Darstellung
#include <fstream>            // Für das Laden und Speichern von Dateien (Scores)

// Struktur für Score-Einträge (Spielername und Punkte)
struct ScoreEntry {
	std::string playerName;  // Name des Spielers
	int playerScore;         // Punkte des Spielers

	// Konstruktor zur Initialisierung eines Score-Eintrags
	ScoreEntry(const std::string& name, int score)
		: playerName(name), playerScore(score) {}

	// Vergleichsoperator, um die Score-Einträge zu sortieren (absteigend)
	bool operator<(const ScoreEntry& other) const {
		return playerScore > other.playerScore;
	}
};

// Klasse für die Verwaltung der Bestenliste (Scoreboard)
class Scoreboard {
public:
	// Konstruktor
	Scoreboard();

	// Methoden für Eingabe, Verarbeitung und Ausgabe (EVA)
	int input(sf::Event& event);            // Verarbeitet die Benutzereingabe
	void update();                          // Aktualisiert den Status des Scoreboards
	void render(sf::RenderWindow& window);  // Zeichnet das Scoreboard auf das Fenster

	// Funktionen für das Hinzufügen, Laden, Speichern und Löschen von Highscores
	void addScore(const std::string& playerName, int score);  // Fügt einen neuen Score hinzu
	void loadScores();                                        // Lädt die gespeicherten Scores aus einer Datei
	void saveScores();                                        // Speichert die Scores in eine Datei
	void clearScores();                                       // Löscht alle Scores (z.B. zum Zurücksetzen)

private:
	// Instanzen für die grafische Darstellung
	sf::Font font;           // Schriftart für die Texte
	sf::Text titleText;       // Text für den Titel der Bestenliste
	sf::Text deleteText;      // Text für die Option, die Scores zu löschen
	sf::Text returnText;      // Text für die Rückkehr zum Hauptmenü
	sf::Text scoreText;       // Text zur Anzeige der Scores
	std::vector<ScoreEntry> scores;  // Liste der Scores (Bestenliste)

	// Variable für die aktuell ausgewählte Option im Scoreboard (z.B. "Löschen" oder "Zurück")
	int selectedScoreboardItem = 0;

	// EVA
	// Verarbeitet den aktuellen Status und die Benutzereingaben im Scoreboard
	int processState(sf::Event& event);       // Verarbeitet die Eingabe (z.B. Menüauswahl)
	void updateTextColors();                  // Aktualisiert die Textfarben basierend auf der Auswahl
	void renderHighscores(sf::RenderWindow& window);  // Zeichnet die Highscores auf das Fenster

	// Funktionen zur Initialisierung und Darstellung der Texte
	void initTextStrings();  // Initialisiert die Texte (z.B. Titel, Menütexte)
	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position); // Zentriert einen Text und setzt Eigenschaften wie Farbe und Position
};

// Ende der Header Guards
#endif
