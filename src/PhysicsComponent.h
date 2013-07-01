#pragma once

#include "SFML\System.hpp"
#include "EntityList.h"
//CONSIDER REMOVING
class PhysicsComponent {
public:

	PhysicsComponent(EntityList *entities, bool stationary, sf::Vector2f position, float height, sf::Vector2f velocity, sf::Vector2f size);

	void update(sf::Time time);

	sf::Vector2f normalize(sf::Vector2f vector);

	sf::Vector2f collision(PhysicsComponent *entity);

	EntityList *_entities;

	bool _stationary;

	sf::Vector2f _velocity;

	sf::Vector2f _position;

	float _height;

	sf::Vector2f _size;

	sf::Vector2f _heading;

};