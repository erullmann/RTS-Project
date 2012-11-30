
#include "BaseEntity.h"

void BaseEntity::start(sf::Vector2f position, int team)
{
	//do nothing
}

void BaseEntity::update(sf::Time frame_time, std::vector<BaseEntity*> entityList, int** map, sf::Vector2f destinationVector, BaseEntity* targetEntity)
{
	//do nothing
}
void BaseEntity::draw(sf::RenderWindow& renderwindow)
{
	//do nothing
}
void BaseEntity::destroy()
{
	//do nothing
}

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

int BaseEntity::returnHeadingSection(float angle)
{
	float pi = 3.14159;

	angle = (8 * (angle)) / pi;

	//find direction the sprite is looking
	if ((angle < 3) && (angle >= 1))
		return 3;
	else if ((angle < 1) && (angle >= -1))
		return 2;
	else if ((angle < -1) && (angle >= -3))
		return 1;
	else if ((angle < -3) && (angle >= -5))
		return 0;
	else if ((angle < -5) && (angle >= -7))
		return 7;
	else if ((angle < -7) || (angle >= 7))
		return 6;
	else if ((angle < 7) && (angle >= 5))
		return 5;
	else
		return 4;
}
