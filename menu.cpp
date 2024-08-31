/* LUMALU
*/
#include "menu.h"
#include "globals.h"
#include <iostream>

// --------------------------------------
// PUBLIC
Menu::Menu()
{
    initTextStrings();
}

// IPO
int Menu::input(sf::Event& event) {
    return processState(event);
}

void Menu::update()
{
    updateTextColors();
}

void Menu::render(sf::RenderWindow& window)
{
    window.clear(gb::colBackground);
    window.draw(titleText);
    window.draw(startText);
    window.draw(highscoreText);
    window.draw(quitText);
    window.draw(helpText);
}

// --------------------------------------
// PRIVAT
int Menu::processState(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W) {
            std::cout << "MENU_W \n"; //DEBUG
            selectedMenuItem = (selectedMenuItem - 1 + 3) % 3;
        }
        else if (event.key.code == sf::Keyboard::S) {
            std::cout << "MENU_S \n"; //DEBUG
            selectedMenuItem = (selectedMenuItem + 1) % 3;
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            std::cout << "MENU_Enter \n"; //DEBUG
            if (selectedMenuItem == 0) {
                return 1; // START
            }
            else if (selectedMenuItem == 1) {
                return 2; // BESTENLISTE
            }
            else if (selectedMenuItem == 2)
            {
                return 0; // BEENDEN
            }
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            std::cout << "MENU_Esc \n"; //DEBUG
            return 0;
        }
    }
}

// TEXT
void Menu::updateTextColors()
{
    startText.setFillColor(selectedMenuItem == 0 ? gb::colTextOn : gb::colTextOff);
    highscoreText.setFillColor(selectedMenuItem == 1 ? gb::colTextOn : gb::colTextOff);
    quitText.setFillColor(selectedMenuItem == 2 ? gb::colTextOn : gb::colTextOff);
}

void Menu::initTextStrings()
{
    font.loadFromFile("Fonts/Dimbo Regular.ttf");
    initCenteredText(titleText, "SNAKE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.2));
    initCenteredText(startText, "START", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.4));
    initCenteredText(highscoreText, "BESTENLISTE", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.5));
    initCenteredText(quitText, "BEENDEN", 50, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.6));
    initCenteredText(helpText, "Steuerung mit W,A,S,D, Enter und Escape", 20, gb::colTextOff, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.95));
}

void Menu::initCenteredText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
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