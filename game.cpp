/* LUMALU
*/
#include "game.h"
#include "globals.h"

#include <cstdlib>
#include <ctime>

Game::Game()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");

    initText(scoreText, "Punkte: ", 70, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.1));

    spawnFruit();
}

void Game::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(scoreText);
    renderArena(window);
    window.draw(fruit);
}

int Game::handleInput(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        return 3;
    }
}

void Game::spawnFruit()
{
    fruit.setRadius(gb::blockSize/2);
    fruit.setFillColor(gb::colFruit);
    int x = std::rand() % gb::arenaWidth;
    int y = std::rand() % gb::arenaHeight;
    fruit.setPosition(x * gb::blockSize,
                      y * gb::blockSize);
}

void Game::renderArena(sf::RenderWindow& window)
{

    int xOffset = (gb::winWidth - (gb::arenaWidth * gb::blockSize)) / 2;
    int yOffset = gb::winHeight - (gb::arenaHeight * gb::blockSize) - 10;

    for (int i = 0; i < gb::arenaHeight; ++i) {
        for (int j = 0; j < gb::arenaWidth; ++j) {
            sf::RectangleShape block(sf::Vector2f(gb::blockSize, gb::blockSize));
            block.setPosition(j * gb::blockSize + xOffset, i * gb::blockSize + yOffset);

            if ((i + j) % 2 == 0)
                block.setFillColor(gb::colArena1);
            else
                block.setFillColor(gb::colArena2);

            window.draw(block);
        }
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
