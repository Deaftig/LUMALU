/* LUMALU
*/
#include "game.h"
#include "globals.h"



Game::Game()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");

    initText(scoreText, "Punkte: ", 70, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.1));

    spawnFruit();
    spawnSnake();
}

void Game::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(scoreText);
    renderArena(window);
    renderFruit(window);
    renderSnake(window);

}

int Game::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W && direction.y == 0)
            direction = sf::Vector2i(0, -1);  // Nach oben
        else if (event.key.code == sf::Keyboard::A && direction.x == 0)
            direction = sf::Vector2i(-1, 0);  // Nach links
        else if (event.key.code == sf::Keyboard::S && direction.y == 0)
            direction = sf::Vector2i(0, 1);   // Nach unten
        else if (event.key.code == sf::Keyboard::D && direction.x == 0)
            direction = sf::Vector2i(1, 0);   // Nach rechts
        else if (event.key.code == sf::Keyboard::Escape)
            return 3;
    }
}

void Game::update()
{
    sf::Vector2i newHeadPosition = snake.front() + direction;

    // Die Schlange bewegt sich
    snake.insert(snake.begin(), newHeadPosition);  // Neuer Kopf
    snake.pop_back();
}



void Game::spawnFruit()
{
    fruit.setRadius(gb::blockSize/2);
    fruit.setFillColor(gb::colFruit);
    int x = std::rand() % gb::arenaWidth;
    int y = std::rand() % gb::arenaHeight;
    fruit.setPosition(x * gb::blockSize + gb::xOffset,
                      y * gb::blockSize + gb::yOffset);
}

void Game::spawnSnake()
{
    int initialLength = 5;
    int startX = gb::arenaWidth / 2;
    int startY = gb::arenaHeight / 2;

    for (int i = 0; i < initialLength; i++) {
        snake.push_back(sf::Vector2i(startX - i, startY));
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
        //snakeSegment.setOutlineThickness(-5);
        //snakeSegment.setOutlineColor(gb::colSecondary);

        window.draw(snakeSegment);
    }
}

void Game::initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
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
