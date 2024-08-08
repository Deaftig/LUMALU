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
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(100, 250, 50));
}


