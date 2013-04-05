/////////////////////
//BaseObject 
//The base class for all ingame objects
/////////////////////
#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"
#include "EntityType.h"

class BaseEntity
{
public:

	virtual void update(sf::Time frameTime); //different for all inheriting objects; will typically make AI, physics and collision calls; if colliding with a dangours object, will take damage

	virtual void draw(); //draws object on screen based on self read conditions

	virtual void destroy(); //dystroys the unit

	virtual sf::Vector2f returnPosition();

	virtual enum ENTITYTYPE returnType();

};