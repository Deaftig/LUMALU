// Header-Dateien
#include "scoreboard.h"
#include "global.h"

// PUBLIC
Scoreboard::Scoreboard() {
    initTextStrings();
    loadScores();
}

// EVA
int Scoreboard::input(sf::Event& event) {
    return processState(event);
}

void Scoreboard::update() {
    updateTextColors();
}

void Scoreboard::render(sf::RenderWindow& window) {
    window.clear(gb::colBackground);
    renderText(window);

}

int Scoreboard::processState(sf::Event& event) {
    if (gb::pressedAnyKey(event)) {
        if (gb::pressedEnter(event)) {
            if (selectedScoreboardItem == 1) {
                clearScores();
            }
            else if (selectedScoreboardItem == 0) {
                return 3; // BESTENLISTE
            }
        }
        else if (gb::pressedEscape(event)) {
            return 3;
        }
        else if (gb::pressedA(event)) {
            selectedScoreboardItem = (selectedScoreboardItem - 1 + 2) % 2;
        }
        else if (gb::pressedD(event)) {
            selectedScoreboardItem = (selectedScoreboardItem + 1) % 2;
        }
    }
    return -1;
}

void Scoreboard::addScore(const std::string& playerName, int score) {
    scores.push_back(ScoreEntry(playerName, score));
    std::sort(scores.begin(), scores.end());  // Sortiere nach Scores
    saveScores();  // Speichere die Scores
}

void Scoreboard::loadScores() {
    std::ifstream file("highscores.txt");
    std::string name;
    int score;
    if (file.is_open()) {
        while (file >> name >> score) {
            scores.push_back(ScoreEntry(name, score));
        }
        file.close();
    }
}

void Scoreboard::saveScores() {
    std::ofstream file("highscores.txt");
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.playerName << " " << entry.playerScore << "\n";
        }
        file.close();
    }
}

void Scoreboard::clearScores() {
    scores.clear(); // Löscht alle Einträge im Scoreboard
    std::ofstream file("highscores.txt", std::ofstream::trunc); // Leert die Datei
    file.close();
}

// TEXT
void Scoreboard::updateTextColors() {
    deleteText.setFillColor(selectedScoreboardItem == 1 ? gb::colFruit : gb::colTextOff);
    returnText.setFillColor(selectedScoreboardItem == 0 ? gb::colTextOn : gb::colTextOff);
}

void Scoreboard::renderText(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(deleteText);
    window.draw(returnText);
    // Render die Highscores (nur die Top 10)
    float yOffset = gb::winHeight * 0.2;
    int count = 0;
    for (const auto& entry : scores) {
        if (count >= 10) break;  // Stoppe nach den Top 10
        sf::Text scoreText;
        initCenteredText(scoreText, entry.playerName + ":  " + std::to_string(entry.playerScore), 30, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, yOffset));
        window.draw(scoreText);
        yOffset += 40; // Abstand zwischen den Einträgen
        count++;  // Zähle die gerenderten Einträge
    }
}

void Scoreboard::initTextStrings() {
    font.loadFromFile("Fonts/Dimbo Regular.ttf");
    initCenteredText(titleText, "BESTENLISTE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.1));
    initCenteredText(deleteText, "LÖSCHEN", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.8, gb::winHeight * 0.9));
    initCenteredText(returnText, "ZURÜCK", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.2, gb::winHeight * 0.9));
}

void Scoreboard::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position) {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position);
}



