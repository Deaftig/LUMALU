/* LUMALU
*/
#include "scoreboard.h"
#include "globals.h"

#include <iostream>


// PUBLIC
Scoreboard::Scoreboard()
{
    initTextStrings();
    std::cout << "Scoreboard initialisert \n"; //DEBUG
}

//IPO
int Scoreboard::input(sf::Event& event) {
    return processState(event);
}

void Scoreboard::update()
{
    updateTextColors();
}

void Scoreboard::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(titleText);
    window.draw(deleteText);
    window.draw(returnText);
}

int Scoreboard::processState(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::A) {
            selectedMenuItem = (selectedMenuItem - 1 + 2) % 2;
        }
        else if (event.key.code == sf::Keyboard::D) {
            selectedMenuItem = (selectedMenuItem + 1) % 2;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            if (selectedMenuItem == 0) {
        // DELETE SCORBOARD
            }
            else if (selectedMenuItem == 1) {
                return 3; // BESTENLISTE
            }
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            return 3;
        }
    }
}

// TEXT
void Scoreboard::updateTextColors() {
    deleteText.setFillColor(selectedMenuItem == 0 ? gb::colFruit : gb::colTextOff);
    returnText.setFillColor(selectedMenuItem == 1 ? gb::colTextOn : gb::colTextOff);
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



