#pragma once

#include "MobileComponent.h"

MobileComponent::MobileComponent(sf::Vector2f position, sf::Vector2f velocity){
	_position = position;
	_velocity = velocity;
	_heading = normalize(velocity);
}

void MobileComponent::update(sf::Time time){
	_position += _velocity * time.asSeconds();
	_heading = normalize(_velocity);
}

sf::Vector2f MobileComponent::normalize(sf::Vector2f vector){
	float lengthSqr = (vector.x * vector.x) + (vector.y * vector.y);
	return vector / lengthSqr;
}