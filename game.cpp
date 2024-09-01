#include "game.h"
#include "globals.h"

#include <iostream>

// PUBLIC
Game::Game()
{
    initTextStrings();
    std::cout << "Game initialisert \n"; //DEBUG
}

// IPO
int Game::input(sf::Event& event) {
    switch (gameOver) {
    case false:
        return processState(event);
        break;
    case true:
        return processState_gameOver(event);
        break;
    }
}

void Game::update()
{
    switch (gameOver) {
    case false:
        updateFruit();
        updateSnake();
        updateCollision();
        break;
    case true:
        break;
    }
}

void Game::render(sf::RenderWindow& window)
{
    switch (gameOver) {
    case false:
        window.clear(gb::colBackground);
        window.draw(activeScoreText);
        renderArena(window);
        renderSnake(window);
        renderFruit(window);
        break;
    case true:
        window.clear(gb::colBackground);
        window.draw(finalText);
        window.draw(finalScoreText);
        window.draw(nameText);
        break;
    }
}

// --------------------------------------
// PRIVAT
int Game::processState(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            resetGame();
            return 3;
        }
        if (event.key.code == sf::Keyboard::X) {
            gameOver = true; // DEBUG
        }
        if (event.key.code == sf::Keyboard::W && direction.y == 0) {
            direction = sf::Vector2i(0, -1);  // Nach oben
        }
        else if (event.key.code == sf::Keyboard::A && direction.x == 0) {
            direction = sf::Vector2i(-1, 0);  // Nach links
        }
        else if (event.key.code == sf::Keyboard::S && direction.y == 0) {
            direction = sf::Vector2i(0, 1);   // Nach unten
        }
        else if (event.key.code == sf::Keyboard::D && direction.x == 0) {
            direction = sf::Vector2i(1, 0);   // Nach rechts
        }
    }
}

int Game::processState_gameOver(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) { snakeActive = false;fruitActive = false;return 3; }
        if (event.key.code == sf::Keyboard::Enter) {resetGame(); return 3; }
    }
    if (event.type == sf::Event::TextEntered) {
        char enteredChar = static_cast<char>(event.text.unicode);

        // Überprüfen, ob es ein Großbuchstabe (A-Z) ist
        if (enteredChar >= 'A' && enteredChar <= 'Z') {
            if (playerName.length() < 6) {  // Beschränkung auf 6 Zeichen
                playerName += enteredChar;
                nameText.setString("NAME: " + playerName);
            }
        }
        // Überprüfen, ob es ein Kleinbuchstabe (a-z) ist und umwandeln in Großbuchstabe
        else if (enteredChar >= 'a' && enteredChar <= 'z') {
            if (playerName.length() < 6) {
                playerName += static_cast<char>(enteredChar - 32);  // Umwandeln in Großbuchstabe
                nameText.setString("NAME: " + playerName);
            }
        }
        // Verarbeiten der Rücktaste (Löschen des letzten Buchstabens)
        else if (event.text.unicode == 8 && !playerName.empty()) { playerName.pop_back(); nameText.setString("NAME: " + playerName); }
    }
}

// SPAWN
void Game::spawnFruit() {
    // Frucht an einer zufälligen Position spawnen
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Bestimme die Position der Frucht
    sf::Vector2i fruitPosition;
    bool positionValid = false;

    while (!positionValid) {
        fruitPosition.x = std::rand() % gb::arenaWidth;
        fruitPosition.y = std::rand() % gb::arenaHeight;

        // Überprüfe, ob die Fruchtposition auf der Schlange liegt
        positionValid = true;  // Gehe davon aus, dass die Position gültig ist

        for (const auto& segment : snake) {
            if (segment == fruitPosition) {
                positionValid = false;  // Position ist nicht gültig, weil sie auf der Schlange liegt
                break;  // Breche die Schleife ab, um eine neue Position zu wählen
            }
        }
    }

    // Setze die Fruchtposition
    fruit.setRadius(gb::blockSize / 2);
    fruit.setFillColor(gb::colFruit);
    fruit.setPosition(fruitPosition.x * gb::blockSize + gb::xOffset,
        fruitPosition.y * gb::blockSize + gb::yOffset);

    std::cout << "Frucht erzeugt bei X: " << fruit.getPosition().x << ", Y: " << fruit.getPosition().y << std::endl; // DEBUG
}


void Game::spawnSnake() {
    int initialLength = 5;
    int startX = gb::arenaWidth / 2;
    int startY = gb::arenaHeight / 2;

    for (int i = 0; i < initialLength; i++) {
        snake.push_back(sf::Vector2i(startX - i, startY));
    }
    direction = sf::Vector2i(1, 0);
    snakeActive = true;

    std::cout << "Schlange erzeugt \n"; //DEBUG
}

void Game::resetGame()
{
    initTextStrings();
    gameOver = false;
    snakeActive = false;
    fruitActive = false;
    playerName = "";
    playerScore = 0;
    snake.clear();
    growSnake = false; // Sicherstellen, dass die Schlange beim Neustart nicht wächst
}


void Game::updateCollision()
{
    if (snake.empty()) {
        return; // Nichts zu überprüfen, wenn die Schlange leer ist
    }

    // Kollisionsüberprüfung zwischen Schlange und Frucht
    sf::Vector2f fruitPosition = fruit.getPosition();
    sf::Vector2f newHeadPositionFloat(snake.front().x * gb::blockSize + gb::xOffset,
        snake.front().y * gb::blockSize + gb::yOffset);

    if (fruitPosition == newHeadPositionFloat) {
        std::cout << "Kollision entdeckt, neue Frucht wird erzeugt\n"; // DEBUG
        playerScore++;
        activeScoreText.setString("PUNKTE: " + std::to_string(playerScore));
        spawnFruit();  // Erzeuge eine neue Frucht
        growSnake = true; // Schlange soll wachsen
    }

    // Kollisionsüberprüfung mit der Wand
    sf::Vector2i headPosition = snake.front();
    if (headPosition.x < 0 || headPosition.x >= gb::arenaWidth ||
        headPosition.y < 0 || headPosition.y >= gb::arenaHeight) {
        std::cout << "Kollision mit der Wand! \n"; // DEBUG
        finalScoreText.setString("PUNKTE: " + std::to_string(playerScore));
        gameOver = true;
        return;
    }

    // Kollisionsüberprüfung mit dem eigenen Körper
    for (size_t i = 1; i < snake.size(); ++i) {
        if (headPosition == snake[i]) {
            std::cout << "Kollision mit dem eigenen Körper! \n"; // DEBUG
            finalScoreText.setString("PUNKTE: " + std::to_string(playerScore));
            gameOver = true;
            return;
        }
    }
}


// UPDATE
void Game::updateFruit()
{
    if (!fruitActive) {
        spawnFruit();  // Frucht erzeugen
        fruitActive = true;
    }
}

void Game::updateSnake()
{
    if (!snakeActive) {
        spawnSnake();
    }

    moveInterval = sf::seconds(1.f);
    if (moveClock.getElapsedTime() >= moveInterval) {
        if (!snake.empty()) {
            // Speichere die aktuelle Kopfposition
            sf::Vector2i newHeadPosition = snake.front();
            // Bewege den Kopf in die aktuelle Richtung
            newHeadPosition += direction;

            // Füge die neue Kopfposition zur Schlange hinzu
            snake.insert(snake.begin(), newHeadPosition);

            // Wenn growSnake gesetzt ist, entferne das letzte Segment nicht
            if (!growSnake) {
                snake.pop_back();
            }
            else {
                growSnake = false; // Nach einmaligem Wachstum zurücksetzen
            }
        }
        moveClock.restart();
    }
}

// RENDER
void Game::renderArena(sf::RenderWindow& window)
{
    for (int i = 0; i < gb::arenaHeight; ++i) {
        for (int j = 0; j < gb::arenaWidth; ++j) {
            sf::RectangleShape block(sf::Vector2f(gb::blockSize, gb::blockSize));
            block.setPosition(j * gb::blockSize + gb::xOffset,
                              i * gb::blockSize + gb::yOffset);
            

            if ((i + j) % 2 == 0)
                block.setFillColor(gb::colArena1);
            else
                block.setFillColor(gb::colArena2);

            window.draw(block);
        }
    }
}

void Game::renderFruit(sf::RenderWindow& window)
{
    window.draw(fruit);
}

void Game::renderSnake(sf::RenderWindow& window)
{
    for (const auto& segment : snake) {
        sf::RectangleShape snakeSegment(sf::Vector2f(gb::blockSize, gb::blockSize));
        snakeSegment.setPosition(segment.x * gb::blockSize + gb::xOffset,
                                 segment.y * gb::blockSize + gb::yOffset);
        snakeSegment.setFillColor(gb::colSnake);
        window.draw(snakeSegment);
    }
}

// TEXT
void Game::initTextStrings()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");
    initCenteredText(activeScoreText, "PUNKTE: 0", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.4, gb::winHeight * 0.1));
    initCenteredText(finalText, "SPIEL BEENDET!", 90, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.2));
    initCenteredText(finalScoreText, "PUNKTE: XX", 70, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.4));
    initCenteredText(nameText, "NAME: PLAYER", 70, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.6));
    initCenteredText(againText, "NEUSTART", 50, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.8, gb::winHeight * 0.9));
    initCenteredText(returnText, "ZURÜCK", 50, gb::colTextOff, sf::Vector2f(gb::winWidth * 0.2, gb::winHeight * 0.9));
}

void Game::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
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

