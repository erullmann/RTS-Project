
#pragma once
#include "BaseEntity.h"

bool BaseEntity::returnDeleteFlag()
{
	return isDeletable;
}

bool BaseEntity::returnPassableFlag()
{
	return isPassable;
}

float BaseEntity::returnDamage()
{
	return damage;
}

sf::Vector2i BaseEntity::returnSize()
{
	return size;
}

sf::Vector2f BaseEntity::returnPosition()
{
	return position;
}

int BaseEntity::returnTeam()
{
	return team;
}
