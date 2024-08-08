// Header-Dateien
#include "globals.h"
#include "menu.h"

// Basis-Bibliotheken
#include <iostream>

Menu::Menu()
{
    if (!font.loadFromFile("Fonts/Dimbo Regular.ttf"))
    {
        std::cerr << "Fehler beim Laden der Schriftart" << std::endl;
    }

    // Darstellen der Schrift im Hauptmenü
    initText(titleText, "SNAKE", 90, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.2));             // Initialisieren des Textes "SNAKE", in Abhängigkeit der Fenstergröße
    initText(startText, "START", 50, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.4));             //          -||-             "START",              -||-        
    initText(highscoreText, "HIGHSCORE", 50, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.5));     //          -||-             "HIGHSCORE",          -||-        
    initText(quitText, "BEENDEN", 50, gb::colTextOn, sf::Vector2f(gb::winWidth / 2, gb::winHeight * 0.6));            //          -||-             "BEENDEN",            -||-        

    selectedItem = 0;   // "START" als ausgewählt festlegen
    updateTextColors(); // Aufruf der Funktion, welche die einzelnen Menüpunkte, je nach aktueller Auswahl, farbig hinterlegt
}

void Menu::handleInput(sf::RenderWindow& window)
{
}

void Menu::update()
{
}

void Menu::render(sf::RenderWindow& window)
{
}

void Menu::initText(sf::Text& text, const std::string& string, unsigned int size, sf::Color color, sf::Vector2f position)
{
}

void Menu::updateTextColors()
{
}
