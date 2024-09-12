// Header Guards
#ifndef GLOBAL_FUNC
#define GLOBAL_FUNC

// SFML-Bibliotheken
#include <SFML/Graphics.hpp>

namespace gb {

	// Input
	bool pressedEnter(sf::Event& event) {
		return event.key.code == sf::Keyboard::Enter;
	}

	bool pressedEscape(sf::Event& event) {
		return event.key.code == sf::Keyboard::Escape;
	}

	bool pressedW(sf::Event& event) {
		return event.key.code == sf::Keyboard::W;
	}

	bool pressedA(sf::Event& event) {
		return event.key.code == sf::Keyboard::A;
	}

	bool pressedS(sf::Event& event) {
		return event.key.code == sf::Keyboard::S;
	}

	bool pressedD(sf::Event& event) {
		return event.key.code == sf::Keyboard::D;
	}
}

#endif