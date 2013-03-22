#pragma once
/*
file: PathfindComponent.h
Extends the MobileComponent class which is added to entities for movement
Handles pathfinding to a destination
*/

#include "EntityList.h"
#include "MobileComponent.h"
enum MOVESTATE{
	HALTED,
	CRAWLING,
	WALKING,
	RUNNING
};

class PathfindComponent :public MobileComponent {
public:

	PathfindComponent(sf::Vector2f position, sf::Vector2f heading, EntityList *map, EntityList *entities, float maxspeed);

	~PathfindComponent();

	//AI/User commands//

	//sets final destination for entity, entity will follow path to here
	//dest is in absolute map terms
	void setDestination(sf::Vector2f dest);

	//set maxspeed to whatever
	void setSpeed(float maxspeed);

	//set movement speed (halt to stop)
	//crawl is 0.5*_speed
	//walk is 1.0*_speed
	//run is 1.25*_speed
	void setMoveState(MOVESTATE state);

	//returns current speed
	enum MOVESTATE getMoveState();

	//returns current final destination
	sf::Vector2f getDestination();

	//returns true if at final destination
	bool atDestination();

	//Auto commands//

	//updates position, etc
	void update(sf::Time time);

private:

	void findRoute(sf::Vector2f dest);

	float getSpeedModifier(MOVESTATE state);

	EntityList *_map;

	EntityList *_entities;

	std::vector<sf::Vector2f> _route;

	MOVESTATE _movestate;

	float _maxspeed;
	
};