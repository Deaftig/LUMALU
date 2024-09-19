// Header Guards verhindern, dass die Datei mehrfach inkludiert wird
#ifndef SCOREBOARD
#define SCOREBOARD

// Einbindung der notwendigen Bibliotheken
#include <SFML/Graphics.hpp>  // F�r die grafische Darstellung
#include <fstream>            // F�r das Laden und Speichern von Dateien (Scores)

// Struktur f�r Score-Eintr�ge (Spielername und Punkte)
struct ScoreEntry {
	std::string playerName;  // Name des Spielers
	int playerScore;         // Punkte des Spielers

	// Konstruktor zur Initialisierung eines Score-Eintrags
	ScoreEntry(const std::string& name, int score)
		: playerName(name), playerScore(score) {}

	// Vergleichsoperator, um die Score-Eintr�ge zu sortieren (absteigend)
	bool operator<(const ScoreEntry& other) const {
		return playerScore > other.playerScore;
	}
};

// Klasse f�r die Verwaltung der Bestenliste (Scoreboard)
class Scoreboard {
public:
	// Konstruktor
	Scoreboard();

	// Methoden f�r Eingabe, Verarbeitung und Ausgabe (EVA)
	int input(sf::Event& event);            // Verarbeitet die Benutzereingabe
	void update();                          // Aktualisiert den Status des Scoreboards
	void render(sf::RenderWindow& window);  // Zeichnet das Scoreboard auf das Fenster

	// Funktionen f�r das Hinzuf�gen, Laden, Speichern und L�schen von Highscores
	void addScore(const std::string& playerName, int score);  // F�gt einen neuen Score hinzu
	void loadScores();                                        // L�dt die gespeicherten Scores aus einer Datei
	void saveScores();                                        // Speichert die Scores in eine Datei
	void clearScores();                                       // L�scht alle Scores (z.B. zum Zur�cksetzen)

private:
	// Instanzen f�r die grafische Darstellung
	sf::Font font;           // Schriftart f�r die Texte
	sf::Text titleText;       // Text f�r den Titel der Bestenliste
	sf::Text deleteText;      // Text f�r die Option, die Scores zu l�schen
	sf::Text returnText;      // Text f�r die R�ckkehr zum Hauptmen�
	sf::Text scoreText;       // Text zur Anzeige der Scores
	std::vector<ScoreEntry> scores;  // Liste der Scores (Bestenliste)

	// Variable f�r die aktuell ausgew�hlte Option im Scoreboard (z.B. "L�schen" oder "Zur�ck")
	int selectedScoreboardItem = 0;

	// EVA
	// Verarbeitet den aktuellen Status und die Benutzereingaben im Scoreboard
	int processState(sf::Event& event);       // Verarbeitet die Eingabe (z.B. Men�auswahl)
	void updateTextColors();                  // Aktualisiert die Textfarben basierend auf der Auswahl
	void renderHighscores(sf::RenderWindow& window);  // Zeichnet die Highscores auf das Fenster

	// Funktionen zur Initialisierung und Darstellung der Texte
	void initTextStrings();  // Initialisiert die Texte (z.B. Titel, Men�texte)
	void initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position); // Zentriert einen Text und setzt Eigenschaften wie Farbe und Position
};

// Ende der Header Guards
#endif
