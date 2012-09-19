/////////////////////
//BaseObject 
//The base class for all ingame objects
/////////////////////
#pragma once;
#include <iostream>
#include "SFML\Graphics.hpp"


class BaseEntity
{
public:

	virtual void start(sf::Vector2f position) =0; //starting implementer call, must be called for all objects

	virtual void update(int& level, std::vector<BaseEntity*>& objectList) =0; //different for all inheriting objects; will typically make AI, physics and collision calls; if colliding with a dangours object, will take damage

	virtual void draw(sf::RenderWindow& renderwindow) =0;//draws object on screen based on self read conditions

	bool returnDeleteFlag();

	bool returnPassableFlag();

	float returnDamage();

	sf::Vector2i returnSize();

	sf::Vector2f returnPosition();

	int returnTeam();
	
private:

	sf::Vector2i size;//size of object in pixels (blocks are 32x32)

	sf::Vector2f position; //NULL for player inventory

	bool isDeletable;

	bool isPassable;

	float damage; //0 for non damaging entities

	enum e_team {NEUTRAL, ALLY, ENEMY}; 

	e_team team;

};