#pragma once

#include "SFML\System.hpp"

class MobileComponent {
public:

	MobileComponent(sf::Vector2f position, sf::Vector2f velocity);

	void update(sf::Time time);

	sf::Vector2f normalize(sf::Vector2f vector);

	sf::Vector2f _velocity;

	sf::Vector2f _position;

	sf::Vector2f _heading;

};