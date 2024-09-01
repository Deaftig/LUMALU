/* LUMALU
*/
#ifndef GLOBALS
#define GLOBALS

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>

namespace gb
{
	// Farben
	const sf::Color colFruit(202, 83, 51);
	const sf::Color colTextOff(200, 200, 200);
	const sf::Color colTextOn(255, 255, 255);
	const sf::Color colSnake(94, 115, 223, 255);
	const sf::Color colBackground(51, 70, 118, 255);
	const sf::Color colSecondary(66, 91, 157, 255);
	const sf::Color colArena1(188, 206, 244, 255);
	const sf::Color colArena2(173, 195, 239, 255);

	// Fenstergröße
	const int winWidth = 600;
	const int winHeight = 600;

	// Arena
	const int blockSize = 30;
	const int arenaWidth = 18;
	const int arenaHeight = 16;
	const int xOffset = ((gb::winWidth - (gb::arenaWidth * gb::blockSize)) / 2); // (600 - (18 * 30)) / 2 = 330
	const int yOffset = (gb::winHeight - (gb::arenaHeight * gb::blockSize) - 10); // 600 - (16 * 30) - 10  = 110
}

#endif

