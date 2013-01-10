///////////////////////////////
//Tank.h Tank Class header file
//Tank unit
//-mobile
//-user controlled
//-rotating turret
//-can attack while moving
/////////////////////////////
#pragma once
#include "BaseEntity.h"

class Tank: public BaseEntity
{
public:

	void start(sf::Vector2f position, int team); //starting implementer call, must be called for all objects

	void update(sf::Time frame_time, std::vector<BaseEntity*> entityList, int** map, sf::Vector2f destinationVector, BaseEntity* targetEntity); //will typically make AI, physics, movement and collision 
																   //calls; if colliding with a dangours object, will take damage

	void draw(sf::RenderWindow& renderwindow);//draws object on screen based on self read conditions

	void destroy(); //dystroys the unit

	void setDestination(sf::Vector2f destination); //sets destination for pathfinding

	void setTarget(int targetID); //used for player's setting the units target

	void attack(int targetID);

private:

	sf::Texture tex_turret;
	sf::Texture tex_body;

	sf::Sprite spt_turret;
	sf::Sprite spt_body;

	int stat_HPmax;
	int stat_HPcurr;
	
	float stat_attack;
	float stat_armour;

	float stat_LOS;

	int team_num;

	sf::Vector2f position;

	sf::Vector2f destination;

	float speed_max;
	float speed_curr;
	sf::Vector2f velocity;
	float speed_turn;
	float speed_acceleration;
	
	int body_facing;//number that indicates the direction the body is faceing
	int turret_facing;//divided by 8 to get direction
	int target_ID;
	int type;
};