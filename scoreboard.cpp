// Header-Dateien f�r das Scoreboard und globale Funktionen/Variablen
#include "scoreboard.h"
#include "global.h"

// PUBLIC-Bereich der Scoreboard-Klasse

// Konstruktor: Initialisiert die Texte und l�dt die gespeicherten Scores
Scoreboard::Scoreboard() {
    initTextStrings();  // Initialisiert die Texte (z.B. Titel, Optionen)
    loadScores();       // L�dt die Highscores aus einer Datei
}

// EVA: Eingabe-Verarbeitung-Ausgabe

// Verarbeitet die Benutzereingabe (event) und ruft die entsprechende Methode auf
int Scoreboard::input(sf::Event& event) {
    return processState(event);  // �bergibt das Event an die Statusverarbeitung
}

// Aktualisiert die Textfarben basierend auf der aktuellen Auswahl im Men�
void Scoreboard::update() {
    updateTextColors();
}

// Zeichnet das Scoreboard auf das Fenster (rendering)
void Scoreboard::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);  // Fenster mit Hintergrundfarbe l�schen
    window.draw(titleText);           // Titel zeichnen
    window.draw(deleteText);          // "L�schen"-Option zeichnen
    window.draw(returnText);          // "Zur�ck"-Option zeichnen
    renderHighscores(window);         // Die Highscores anzeigen
}

// PRIVATE-Bereich

// Verarbeitet den Zustand der Benutzereingabe (Tastendr�cke)
int Scoreboard::processState(sf::Event& event) {
    // �berpr�ft, ob eine Taste gedr�ckt wurde
    if (gb::pressedAnyKey(event)) {
        // �berpr�ft, ob die Enter-Taste gedr�ckt wurde
        if (gb::pressedEnter(event)) {
            // Wenn die Option "L�schen" ausgew�hlt ist
            if (selectedScoreboardItem == 1) {
                clearScores();  // L�scht alle Scores
            }
            // Wenn die Option "Zur�ck" ausgew�hlt ist
            else if (selectedScoreboardItem == 0) {
                return 3;  // R�ckkehr zum Hauptmen� (z.B. BESTENLISTE)
            }
        }
        // �berpr�ft, ob die Escape-Taste gedr�ckt wurde
        else if (gb::pressedEscape(event)) {
            return 3;  // R�ckkehr zum Hauptmen�
        }
        // �berpr�ft, ob die linke Taste gedr�ckt wurde (Men�navigation)
        else if (gb::pressedA(event)) {
            // Zyklische Navigation im Men� (nach oben)
            selectedScoreboardItem = (selectedScoreboardItem - 1 + 2) % 2;
        }
        // �berpr�ft, ob die rechte Taste gedr�ckt wurde (Men�navigation)
        else if (gb::pressedD(event)) {
            // Zyklische Navigation im Men� (nach unten)
            selectedScoreboardItem = (selectedScoreboardItem + 1) % 2;
        }
    }
    return -1;  // Keine Zustands�nderung
}

// F�gt einen neuen Score zur Liste hinzu und sortiert die Scores absteigend
void Scoreboard::addScore(const std::string& playerName, int score) {
    scores.push_back(ScoreEntry(playerName, score));  // Neuer Score wird hinzugef�gt
    std::sort(scores.begin(), scores.end());          // Liste wird sortiert (h�chste Scores zuerst)
    saveScores();  // Scores werden nach der �nderung gespeichert
}

// L�dt die Scores aus einer Datei ("highscores.txt")
void Scoreboard::loadScores() {
    std::ifstream file("highscores.txt");  // �ffnet die Datei
    std::string name;
    int score;

    // Wenn die Datei erfolgreich ge�ffnet wurde
    if (file.is_open()) {
        // Liest die Scores (Name und Punktzahl) zeilenweise aus
        while (file >> name >> score) {
            scores.push_back(ScoreEntry(name, score));  // F�gt jeden Eintrag zur Liste hinzu
        }
        file.close();  // Schlie�t die Datei
    }
}

// Speichert die Scores in einer Datei ("highscores.txt")
void Scoreboard::saveScores() {
    std::ofstream file("highscores.txt");  // �ffnet die Datei im Schreibmodus
    if (file.is_open()) {
        // Schreibt jeden Score in die Datei (Name und Punktzahl)
        for (const auto& entry : scores) {
            file << entry.playerName << " " << entry.playerScore << "\n";
        }
        file.close();  // Schlie�t die Datei
    }
}

// L�scht alle Scores und leert die Highscore-Datei
void Scoreboard::clearScores() {
    scores.clear();  // L�scht alle Eintr�ge in der Score-Liste
    std::ofstream file("highscores.txt", std::ofstream::trunc);  // �ffnet die Datei und leert sie
    file.close();  // Schlie�t die Datei
}

// Aktualisiert die Farben der Men�texte basierend auf der aktuellen Auswahl
void Scoreboard::updateTextColors() {
    // Setzt die Farbe des "L�schen"-Texts abh�ngig von der Auswahl
    deleteText.setFillColor(selectedScoreboardItem == 1 ? gb::colFruit : gb::colTextOff);
    // Setzt die Farbe des "Zur�ck"-Texts abh�ngig von der Auswahl
    returnText.setFillColor(selectedScoreboardItem == 0 ? gb::colTextOn : gb::colTextOff);
}

// Zeichnet die Highscores auf das Fenster, zeigt nur die Top 10
void Scoreboard::renderHighscores(sf::RenderWindow& window) {
    float yOffset = gb::winHeight * 0.2;  // Anfangs-Y-Position f�r die Scores
    int count = 0;  // Z�hlt die gerenderten Scores

    // Iteriert �ber die Score-Liste und zeichnet jeden Eintrag
    for (const auto& entry : scores) {
        if (count >= 10) break;  // Stoppt, wenn 10 Scores angezeigt wurden
        // Zentriert und zeichnet jeden Score (Name und Punktzahl)
        initCenteredText(scoreText, entry.playerName + ":  " + std::to_string(entry.playerScore), 30, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, yOffset));
        window.draw(scoreText);
        yOffset += 40;  // Abstand zwischen den einzelnen Scores
        count++;  // Z�hlt die gerenderten Scores
    }
}

// Initialisiert die Texte des Scoreboards (z.B. Titel, Men�texte)
void Scoreboard::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf");  // L�dt die Schriftart aus einer Datei
    initCenteredText(titleText, "BESTENLISTE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.1));  // Initialisiert den Titeltext "BESTENLISTE"
    initCenteredText(deleteText, "L�SCHEN", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.8, gb::winHeight * 0.9));     // Initialisiert den "L�SCHEN"-Text
    initCenteredText(returnText, "ZUR�CK", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.2, gb::winHeight * 0.9));      // Initialisiert den "ZUR�CK"-Text
}

// Zentriert einen Text und setzt die Eigenschaften (Gr��e, Farbe, Position)
void Scoreboard::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(font);  // Setzt die Schriftart
    text.setString(string);  // Setzt den Textinhalt
    text.setCharacterSize(size);  // Setzt die Schriftgr��e
    text.setFillColor(color);  // Setzt die Schriftfarbe
    text.setPosition(position);  // Setzt die Position des Texts
    // Berechnet die Textgrenzen und zentriert den Text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position);  // Setzt die zentrierte Position erneut
}