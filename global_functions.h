// Header Guards
#ifndef GLOBAL_FUNC
#define GLOBAL_FUNC

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>

namespace gb
{
	// Input
	inline bool pressedAnyKey(sf::Event& event) {
		return event.type == sf::Event::KeyPressed;
	}

	inline bool pressedEnter(sf::Event& event) {
		return event.key.code == sf::Keyboard::Enter;
	}

	inline bool pressedEscape(sf::Event& event) {
		return event.key.code == sf::Keyboard::Escape;
	}

	inline bool pressedW(sf::Event& event) {
		return event.key.code == sf::Keyboard::W;
	}

	inline bool pressedA(sf::Event& event) {
		return event.key.code == sf::Keyboard::A;
	}

	inline bool pressedS(sf::Event& event) {
		return event.key.code == sf::Keyboard::S;
	}

	inline bool pressedD(sf::Event& event) {
		return event.key.code == sf::Keyboard::D;
	}
}

#endif