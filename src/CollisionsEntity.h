//////////////
//Collisions componant
//add to classes that need to deal with collisions with other Entitys and the enviroment
//////////////
#pragma once
#include <iostream>
#include "BaseEntity.h"

class CollisionsComponent: public BaseEntity
{
public:

	sf::Vector2f levelCollisions(int& level); //returns vector from colliding with level

	float damageCollisions(std::vector<BaseEntity*>& EntityList); // returns total damage from colliding with projectiles and enemies

private:

};
