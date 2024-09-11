// Header-Dateien
#include "scoreboard.h"
#include "globals.h"

// PUBLIC
Scoreboard::Scoreboard() {
    initTextStrings();
    loadScores();
    std::cout << "Scoreboard initialisert \n"; //DEBUG
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
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            selectedScoreboardItem = (selectedScoreboardItem - 1 + 2) % 2;
        }
        else if (event.key.code == sf::Keyboard::D) {
            selectedScoreboardItem = (selectedScoreboardItem + 1) % 2;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedScoreboardItem == 1) {
        // DELETE SCORBOARD
            }
            else if (selectedScoreboardItem == 0) {
                return 3; // BESTENLISTE
            }
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            return 3;
        }
    }
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

// TEXT
void Scoreboard::updateTextColors() {
    deleteText.setFillColor(selectedScoreboardItem == 1 ? gb::colFruit : gb::colTextOff);
    returnText.setFillColor(selectedScoreboardItem == 0 ? gb::colTextOn : gb::colTextOff);
}

void Scoreboard::renderText(sf::RenderWindow& window)
{
    window.draw(titleText);
    window.draw(deleteText);
    window.draw(returnText);
    // Render die Highscores
    float yOffset = gb::winHeight * 0.2;
    for (const auto& entry : scores) {
        sf::Text scoreText;
        initCenteredText(scoreText, entry.playerName + ": " + std::to_string(entry.playerScore), 30, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, yOffset));
        window.draw(scoreText);
        yOffset += 40; // Abstand zwischen den Einträgen
    }
}

void Scoreboard::initTextStrings()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");
    initCenteredText(titleText, "BESTENLISTE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.1));
    initCenteredText(deleteText, "LÖSCHEN", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.8, gb::winHeight * 0.9));
    initCenteredText(returnText, "ZURÜCK", 50, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.2, gb::winHeight * 0.9));
}

void Scoreboard::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
{
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position);
}



