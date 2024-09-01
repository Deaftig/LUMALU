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
        return processState_gameOver_false(event);
        break;
    case true:
        return processState_gameOver_true(event);
        break;
    }
}

void Game::update()
{
    switch (gameOver) {
    case false:
        updateFruit();
        updateSnake();
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
        window.clear(gb::colShade);
        window.draw(finalText);
        window.draw(finalScoreText);
        window.draw(nameText);
        break;
    }
}

// --------------------------------------
// PRIVAT
int Game::processState_gameOver_false(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            snakeActive = false;
            fruitActive = false;
            return 3;
        }
        if (event.key.code == sf::Keyboard::X) {
            gameOver = true; // DEBUG
            playerName = ""; // DEBUG
            playerPoints = 0; // DEBUG
            std::cout << "GAME OVER! \n"; //DEBUG
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

int Game::processState_gameOver_true(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            snakeActive = false;
            fruitActive = false;
            return 3;
        }
    }
    if (event.type == sf::Event::TextEntered) {
        char enteredChar = static_cast<char>(event.text.unicode);

        // Überprüfen, ob es ein Großbuchstabe (A-Z) ist
        if (enteredChar >= 'A' && enteredChar <= 'Z') {
            if (playerName.length() < 6) {  // Beschränkung auf 6 Zeichen
                playerName += enteredChar;
                nameText.setString("Name: " + playerName);
            }
        }
        // Überprüfen, ob es ein Kleinbuchstabe (a-z) ist und umwandeln in Großbuchstabe
        else if (enteredChar >= 'a' && enteredChar <= 'z') {
            if (playerName.length() < 6) {
                playerName += static_cast<char>(enteredChar - 32);  // Umwandeln in Großbuchstabe
                nameText.setString("Name: " + playerName);
            }
        }
        // Verarbeiten der Rücktaste (Löschen des letzten Buchstabens)
        else if (event.text.unicode == 8 && !playerName.empty()) {
            playerName.pop_back();
            nameText.setString("Name: " + playerName);
        }
    }
}

// SPAWN
void Game::initFruit() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    fruit.setRadius(gb::blockSize/2);
    fruit.setFillColor(gb::colFruit);
    int randomX = std::rand() % gb::arenaWidth;
    int randomY = std::rand() % gb::arenaHeight;
    fruit.setPosition(randomX * gb::blockSize + gb::xOffset,
                      randomY * gb::blockSize + gb::yOffset);
    fruitActive = true;

    sf::Vector2f fruitPosition = fruit.getPosition(); // DEBUG
    std::cout << "Frucht erzeugt bei X: " << fruitPosition.x << ", Y: " << fruitPosition.y << std::endl; //DEBUG
}

void Game::initSnake() {
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

// UPDATE
void Game::updateFruit()
{
     if (!fruitActive) {
         initFruit();
     }
 }


void Game::updateSnake()
{
    if (!snakeActive) {
        initSnake();
    }
    //moveInterval = sf::seconds(0.5f);
    //sf::Time elapsed = moveClock.restart();
    //if (elapsed >= moveInterval) {
    //    if (!snake.empty()) {
    //        // Speichere die aktuelle Kopfposition
    //        sf::Vector2i newHeadPosition = snake.front();
    //        // Bewege den Kopf in die aktuelle Richtung
    //        newHeadPosition += direction;
    //        // Füge die neue Kopfposition am Anfang der Schlange hinzu
    //        snake.insert(snake.begin(), newHeadPosition);

    //        snake.pop_back();
    //    }
    //    moveClock.restart();
    //}
}




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
    initCenteredText(activeScoreText, "Punkte: ", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.4, gb::winHeight * 0.1));
    initCenteredText(finalText, "Spiel beendet!", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.2));
    initCenteredText(finalScoreText, "Punkte: XX", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.4));
    initCenteredText(nameText, "Name: XXXXXX", 70, gb::colTextOn, sf::Vector2f(gb::winWidth * 0.5, gb::winHeight * 0.6));

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

