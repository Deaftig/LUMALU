#include "game.h"
#include "globals.h"

#include <iostream>

// PUBLIC
Game::Game()
{
    initTextStrings();
    initFruit();
    initSnake();
}

// IPO
int Game::input(sf::Event& event) {
   return processState(event);
}

void Game::update()
{
    updateFruit();
    updateSnake();
}

void Game::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(scoreText);
    renderArena(window);
    renderFruit(window);
    renderSnake(window);
}
// --------------------------------------
// PRIVATE
int Game::processState(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            std::cout << "GAME_Esc \n"; //DEBUG
            gameOver = true;
            update();
            return 3;
        }
        if (!gameOver) {
            if (event.key.code == sf::Keyboard::W && direction.y == 0) {
                std::cout << "GAME_W \n"; //DEBUG
                direction = sf::Vector2i(0, -1);  // Nach oben
            }
            else if (event.key.code == sf::Keyboard::A && direction.x == 0) {
                std::cout << "GAME_A \n"; //DEBUG
                direction = sf::Vector2i(-1, 0);  // Nach links
            }
            else if (event.key.code == sf::Keyboard::S && direction.y == 0) {
                std::cout << "GAME_S \n"; //DEBUG
                direction = sf::Vector2i(0, 1);   // Nach unten
            }
            else if (event.key.code == sf::Keyboard::D && direction.x == 0) {
                std::cout << "GAME_D \n"; //DEBUG
                direction = sf::Vector2i(1, 0);   // Nach rechts

            }
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

    std::cout << "SCchlange erzeugt \n"; //DEBUG
}

// UPDATE
void Game::updateFruit()
{
    if (!gameOver) {
        if (!fruitActive) {
            initFruit();
        }
    }
}

void Game::updateSnake()
{
    if (!gameOver) {
        moveInterval = sf::seconds(0.5f);
        sf::Time elapsed = moveClock.restart();
        if (elapsed >= moveInterval) {
            if (!snake.empty()) {
                // Speichere die aktuelle Kopfposition
                sf::Vector2i newHeadPosition = snake.front();
                // Bewege den Kopf in die aktuelle Richtung
                newHeadPosition += direction;

                // Füge die neue Kopfposition am Anfang der Schlange hinzu
                snake.insert(snake.begin(), newHeadPosition);

                snake.pop_back();
            }
            moveClock.restart();
        }
    }
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
    initText(scoreText, "Punkte: ", 70, gb::colTextOn, sf::Vector2f(gb::winWidth / 4, gb::winHeight * 0.025));
}

void Game::initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
{
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(position);
}
