#pragma once
#include "BaseEntity.h"


void BaseEntity::update(sf::Time frameTime)
{
	//do nothing
}
void BaseEntity::draw()
{
	//do nothing
}
void BaseEntity::destroy()
{
	//do nothing
}

sf::Vector2f BaseEntity::returnPosition(){
	return sf::Vector2f(0, 0);
}


