/*
LOGIC FOR MENU
-NEEDS A SCREEN, WHERE THE OPTIONS ARE DISPLAYED (START, SCOREBOARD, EXIT) AND OPEN THEM
-NEEDS A WAY TO CONTROL BETWEEN THE POINTS (KEYBOARD IS PROBABLY EASIER THAN MOUSE)
*/

// Header-Dateien
#include "globals.h"
#include "menu.h"

// Basis-Bibliotheken
#include <iostream>

Menu::Menu()
{

}

void Menu::handleInput(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			window.close();
	}
}


void Menu::update()
{
}

void Menu::render(sf::RenderWindow& window)
{
	sf::CircleShape shape(50);							// just fooling around to get something on my screen
	shape.setFillColor(sf::Color(100, 250, 50));
}


