#pragma once

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(EntityList *entities, bool stationary, sf::Vector2f position, float height, sf::Vector2f velocity, sf::Vector2f size){
	_position = position;
	_velocity = velocity;
	_heading = normalize(velocity);
	_height = height;
	_size = size;
	_stationary = stationary;
	_entities = entities;
}

void PhysicsComponent::update(sf::Time time){
	if (!_stationary){
		_position += _velocity * time.asSeconds();
		_height -= 9.8 * time.asSeconds();

		if (_velocity.x > 0 || _velocity.y > 0)
			_heading = normalize(_velocity);
		if (_height < 0)
			_height = 0;
	}
}

sf::Vector2f PhysicsComponent::normalize(sf::Vector2f vector){
	float length = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	return vector / length;
}

sf::Vector2f PhysicsComponent::collision(PhysicsComponent *entity){
	float xDiff = _position.x - entity->_position.x;
	float yDiff = _position.y - entity->_position.y;

	if (xDiff < 0){
		xDiff += (_size.x + entity->_size.x);
		if (xDiff < 0)//not touching
			xDiff = 0;
	} else{
		xDiff -= (_size.x + entity->_size.x);
		if (xDiff > 0) //not touching
			xDiff = 0;
	}

	if (yDiff < 0){
		yDiff += (_size.y + entity->_size.y);
		if (yDiff < 0)//not touching
			yDiff = 0;
	} else{
		yDiff -= (_size.y + entity->_size.y);
		if (yDiff > 0) //not touching
			yDiff = 0;
	}

	if (xDiff >= yDiff){
		_position += sf::Vector2f(0, yDiff);
		return sf::Vector2f(0, yDiff);
	} else {
		_position += sf::Vector2f(xDiff, 0);
		return sf::Vector2f(xDiff, 0);
	}
}