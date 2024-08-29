/* LUMALU
*/
#include "scoreboard.h"
#include "globals.h"

#include <iostream>


// PUBLIC
Scoreboard::Scoreboard()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");

    initCenteredText(titleText, "BESTENLISTE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.1));
}

//IPO
int Scoreboard::handleInput(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        return 3;
    }
}

void Scoreboard::update()
{

}

void Scoreboard::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(titleText);
}

// --------------------------------------
// PRIVATE
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