/////////////////////
//BaseObject 
//The base class for all ingame objects
/////////////////////
#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"

class BaseEntity
{
public:

	virtual void start(sf::Vector2f position, int team); //starting implementer call, must be called for all objects

	virtual void update(sf::Time frameTime, std::vector<BaseEntity*> entityList, int** map); //different for all inheriting objects; will typically make AI, physics and collision calls; if colliding with a dangours object, will take damage

	virtual void draw(sf::RenderWindow& renderwindow);//draws object on screen based on self read conditions

	virtual void command(BaseEntity* targetEntity, sf::Vector2f destVector);

	virtual void destroy(); //dystroys the unit

	bool returnDeleteFlag();

	bool returnPassableFlag();

	float returnDamage();//returns the damage delt by the unit (for pojectiles)

	sf::Vector2i returnSize();

	sf::Vector2f returnPosition();

	int returnHeadingSection(float angle); //returns the heading as an int (0-8) for drawing purposes

	int returnTeam();

	bool isActive;

	bool isSelected;
	
private:

	sf::Vector2i size;

	sf::Vector2f position;

	bool isDeletable;

	bool isPassable;

	float damage;

	int team; //Player team number

	int ID;

};