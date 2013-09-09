//WalkerComponent.h
//Implements walking and movement for creatures
//takes destination and direction messsages to go in direction

#pragma once

#include "BaseComponent.h"
#include "PathfindingService.h"
#include "Message.h"

class MoverComponent: public BaseComponent {
public:
	
	//initialize MoverComponent
	//pathfinder is pointer to global pathfinder service
	//startingPos is the starting position of the creature
	//movementType is how the creature moves (fly, swim, walk, etc)
	MoverComponent(BaseEntity* parent, PathfindingService* pathfinder, sf::Vector2i startingPos, MOVEMENTTYPE movementType);

	//reads speeds of creature and the current destination or direction and if the creature is moving
	//if new destination is different then last it requests pathfind from pathfinder service
	//consider making pathfinder asycronos
	void readMessages(std::vector<msg*>* msgBuffer);

	//updates time since last move and position if nessecary
	void update(sf::Time frameTime);

	//posts new position
	void postMessages(std::vector<msg*>* msgBuffer);

private:

	//path created by pathfinding service, keep until new one is needed
	//don't delete end point until we get off it
	std::vector<sf::Vector2i>* _path;

	//the current position
	sf::Vector2i _position;

	//the direction the creature will move in its next move instance 
	//Ex: (1, 0) the creature will go right one space; (-1, -1) the creature will go diagonally up-left
	sf::Vector2i _actualDirection;

	//direction that AI wants to go (round off to get above)
	sf::Vector2f _proposedDirection;

	//destination of creature
	sf::Vector2f _destination;

	//is creature moving this turn?
	bool _moving;

	//is creature moving in a direction? if false moving to destination
	bool _movingInDirection;

	//time it takes for creature to move one meter
	float _totalMoveTime; 

	//time since last move (move when higher then _totalMoveTime)
	float _currMoveTime;

	//how the creature moves (walk, fly, swim, etc.)
	MOVEMENTTYPE _movementType;

	//global pathfinding service
	PathfindingService *_pathfinder;

	//converts _proposedDriection to _actualDirection
	sf::Vector2i roundDirection(sf::Vector2f direction);

};
