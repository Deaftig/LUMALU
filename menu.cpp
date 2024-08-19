/* LUMALU
*/
#include "menu.h"
#include "globals.h"
#include <iostream>

Menu::Menu()
{
    if (!font.loadFromFile("Fonts/Dimbo Regular.ttf"))
    {
        std::cerr << "Fehler beim Laden der Schriftart" << std::endl;
    }

    initText(titleText, "SNAKE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.2));
    initText(startText, "START", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.4));
    initText(highscoreText, "BESTENLISTE", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.5));
    initText(quitText, "BEENDEN", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.6));

    selectedMenuItem = 0;
    updateTextColors();
}

void Menu::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(titleText);
    window.draw(startText);
    window.draw(highscoreText);
    window.draw(quitText);
    window.display();
}

int Menu::handleInput(sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            selectedMenuItem = (selectedMenuItem - 1 + 3) % 3;
            updateTextColors();
        }
        else if (event.key.code == sf::Keyboard::S)
        {
            selectedMenuItem = (selectedMenuItem + 1) % 3;
            updateTextColors();
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            if (selectedMenuItem == 0)
            {
                return 1; // START
            }
            else if (selectedMenuItem == 1)
            {
                return 2; // BESTENLISTE
            }
            else if (selectedMenuItem == 2)
            {
                return 0; // BEENDEN
            }
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            return 0;
        }
    }
}

void Menu::initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
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

void Menu::updateTextColors()
{
    startText.setFillColor(selectedMenuItem == 0 ? gb::colTextOn : gb::colTextOff);
    highscoreText.setFillColor(selectedMenuItem == 1 ? gb::colTextOn : gb::colTextOff);
    quitText.setFillColor(selectedMenuItem == 2 ? gb::colTextOn : gb::colTextOff);
}
