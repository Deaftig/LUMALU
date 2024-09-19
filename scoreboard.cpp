// Header-Dateien für das Scoreboard und globale Funktionen/Variablen
#include "scoreboard.h"
#include "global.h"

// PUBLIC-Bereich der Scoreboard-Klasse

// Konstruktor: Initialisiert die Texte und lädt die gespeicherten Scores
Scoreboard::Scoreboard() {
    initTextStrings();  // Initialisiert die Texte (z.B. Titel, Optionen)
    loadScores();       // Lädt die Highscores aus einer Datei
}

// EVA: Eingabe-Verarbeitung-Ausgabe

// Verarbeitet die Benutzereingabe (event) und ruft die entsprechende Methode auf
int Scoreboard::input(sf::Event& event) {
    return processState(event);  // Übergibt das Event an die Statusverarbeitung
}

// Aktualisiert die Textfarben basierend auf der aktuellen Auswahl im Menü
void Scoreboard::update() {
    updateTextColors();
}

// Zeichnet das Scoreboard auf das Fenster (rendering)
void Scoreboard::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);  // Fenster mit Hintergrundfarbe löschen
    window.draw(titleText);           // Titel zeichnen
    window.draw(deleteText);          // "Löschen"-Option zeichnen
    window.draw(returnText);          // "Zurück"-Option zeichnen
    renderHighscores(window);         // Die Highscores anzeigen
}

// PRIVATE-Bereich

// Verarbeitet den Zustand der Benutzereingabe (Tastendrücke)
int Scoreboard::processState(sf::Event& event) {
    // Überprüft, ob eine Taste gedrückt wurde
    if (gb::pressedAnyKey(event)) {
        // Überprüft, ob die Enter-Taste gedrückt wurde
        if (gb::pressedEnter(event)) {
            // Wenn die Option "Löschen" ausgewählt ist
            if (selectedScoreboardItem == 1) {
                clearScores();  // Löscht alle Scores
            }
            // Wenn die Option "Zurück" ausgewählt ist
            else if (selectedScoreboardItem == 0) {
                return 3;  // Rückkehr zum Hauptmenü (z.B. BESTENLISTE)
            }
        }
        // Überprüft, ob die Escape-Taste gedrückt wurde
        else if (gb::pressedEscape(event)) {
            return 3;  // Rückkehr zum Hauptmenü
        }
        // Überprüft, ob die linke Taste gedrückt wurde (Menünavigation)
        else if (gb::pressedA(event)) {
            // Zyklische Navigation im Menü (nach oben)
            selectedScoreboardItem = (selectedScoreboardItem - 1 + 2) % 2;
        }
        // Überprüft, ob die rechte Taste gedrückt wurde (Menünavigation)
        else if (gb::pressedD(event)) {
            // Zyklische Navigation im Menü (nach unten)
            selectedScoreboardItem = (selectedScoreboardItem + 1) % 2;
        }
    }
    return -1;  // Keine Zustandsänderung
}

// Fügt einen neuen Score zur Liste hinzu und sortiert die Scores absteigend
void Scoreboard::addScore(const std::string& playerName, int score) {
    scores.push_back(ScoreEntry(playerName, score));  // Neuer Score wird hinzugefügt
    std::sort(scores.begin(), scores.end());          // Liste wird sortiert (höchste Scores zuerst)
    saveScores();  // Scores werden nach der Änderung gespeichert
}

// Lädt die Scores aus einer Datei ("highscores.txt")
void Scoreboard::loadScores() {
    std::ifstream file("highscores.txt");  // Öffnet die Datei
    std::string name;
    int score;

    // Wenn die Datei erfolgreich geöffnet wurde
    if (file.is_open()) {
        // Liest die Scores (Name und Punktzahl) zeilenweise aus
        while (file >> name >> score) {
            scores.push_back(ScoreEntry(name, score));  // Fügt jeden Eintrag zur Liste hinzu
        }
        file.close();  // Schließt die Datei
    }
}

// Speichert die Scores in einer Datei ("highscores.txt")
void Scoreboard::saveScores() {
    std::ofstream file("highscores.txt");  // Öffnet die Datei im Schreibmodus
    if (file.is_open()) {
        // Schreibt jeden Score in die Datei (Name und Punktzahl)
        for (const auto& entry : scores) {
            file << entry.playerName << " " << entry.playerScore << "\n";
        }
        file.close();  // Schließt die Datei
    }
}

// Löscht alle Scores und leert die Highscore-Datei
void Scoreboard::clearScores() {
    scores.clear();  // Löscht alle Einträge in der Score-Liste
    std::ofstream file("highscores.txt", std::ofstream::trunc);  // Öffnet die Datei und leert sie
    file.close();  // Schließt die Datei
}

// Aktualisiert die Farben der Menütexte basierend auf der aktuellen Auswahl
void Scoreboard::updateTextColors() {
    // Setzt die Farbe des "Löschen"-Texts abhängig von der Auswahl
    deleteText.setFillColor(selectedScoreboardItem == 1 ? gb::colFruit : gb::colTextOff);
    // Setzt die Farbe des "Zurück"-Texts abhängig von der Auswahl
    returnText.setFillColor(selectedScoreboardItem == 0 ? gb::colTextOn : gb::colTextOff);
}

// Zeichnet die Highscores auf das Fenster, zeigt nur die Top 10
void Scoreboard::renderHighscores(sf::RenderWindow& window) {
    float yOffset = gb::winHeight * 0.2;  // Anfangs-Y-Position für die Scores
    int count = 0;  // Zählt die gerenderten Scores

    // Iteriert über die Score-Liste und zeichnet jeden Eintrag
    for (const auto& entry : scores) {
        if (count >= 10) break;  // Stoppt, wenn 10 Scores angezeigt wurden
        // Zentriert und zeichnet jeden Score (Name und Punktzahl)
        initCenteredText(scoreText, entry.playerName + ":  " + std::to_string(entry.playerScore), 30, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, yOffset));
        window.draw(scoreText);
        yOffset += 40;  // Abstand zwischen den einzelnen Scores
        count++;  // Zählt die gerenderten Scores
    }
}

// Initialisiert die Texte des Scoreboards (z.B. Titel, Menütexte)
void Scoreboard::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf");  // Lädt die Schriftart aus einer Datei
    initCenteredText(titleText, "BESTENLISTE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.1));  // Initialisiert den Titeltext "BESTENLISTE"
    initCenteredText(deleteText, "LÖSCHEN", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.8, gb::winHeight * 0.9));     // Initialisiert den "LÖSCHEN"-Text
    initCenteredText(returnText, "ZURÜCK", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.2, gb::winHeight * 0.9));      // Initialisiert den "ZURÜCK"-Text
}

// Zentriert einen Text und setzt die Eigenschaften (Größe, Farbe, Position)
void Scoreboard::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(font);  // Setzt die Schriftart
    text.setString(string);  // Setzt den Textinhalt
    text.setCharacterSize(size);  // Setzt die Schriftgröße
    text.setFillColor(color);  // Setzt die Schriftfarbe
    text.setPosition(position);  // Setzt die Position des Texts
    // Berechnet die Textgrenzen und zentriert den Text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position);  // Setzt die zentrierte Position erneut
}