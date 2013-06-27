#pragma once

#include "PathfindComponent.h"

//utility function that rounds off numbers
float round(float x){
	return floor(x + 0.5);
}

PathfindComponent::PathfindComponent(sf::Vector2f position, sf::Vector2f heading, EntityList *map, EntityList *entities, float speed):
	PhysicsComponent(entities, false, position, 0, sf::Vector2f(0, 0), sf::Vector2f(0.5, 0.5)){
	_map = map;
	_movestate = WALKING;
	_maxspeed = speed;
	_route.reserve(10);
	_heading = heading;
	_position = position;
	_velocity = sf::Vector2f(0, 0);
}

PathfindComponent::~PathfindComponent(){

}

void PathfindComponent::setDestination(sf::Vector2f dest){
	findRoute(dest);
}

void PathfindComponent::setSpeed(float maxspeed){
	_maxspeed = maxspeed;

	_velocity = _heading * (maxspeed * getSpeedModifier(_movestate));
}

void PathfindComponent::setMoveState(MOVESTATE state){
	_movestate = state;
}

enum MOVESTATE PathfindComponent::getMoveState(){
	return _movestate;
}

sf::Vector2f PathfindComponent::getDestination(){
	return _route.front();
}

bool PathfindComponent::atDestination(){
	if (abs(_route.back().x - _position.x) <= 0.1 && abs(_route.back().y - _position.y) <= 0.1){
		_position = _route.back();
		return true;
	} else {
		return false;
	}
}

void PathfindComponent::update(sf::Time time){
	if (atDestination()){
		_route.pop_back();
		_heading = normalize(_route.back() - _position);
		_velocity = _heading * (_maxspeed * getSpeedModifier(_movestate));
	} else if(!_route.empty()) {
		//just keep going to destination
		_heading = normalize(_route.back() - _position);
		_velocity = _heading * (_maxspeed * getSpeedModifier(_movestate));

	}else{
		_movestate = HALTED;
		_velocity = sf::Vector2f(0, 0);
	}

	PhysicsComponent::update(time);
}

void PathfindComponent::findRoute(sf::Vector2f dest){
	//clear old route
	_route.clear();

	

	//start tile is closest tile to the entity
	Tile *start = returnTileEntity(sf::Vector2f(round(this->_position.x), round(this->_position.y)));
	Tile *destination = returnTileEntity(dest);
	EntityList closedSet;
	EntityListIterator closedIter(&closedSet);

	EntityList openSet;
	EntityListIterator openIter(&openSet);
	openSet.pushBack(start);
	start->_nodeComponent->updateFscore(dest, 0);

	while(openSet.length() != 0){
		Tile *current = returnLowestFScore(&openSet);

		if (current == destination){
			Tile *currPath = destination;

			//create new route from current position (at end of route stack) to dest (at front of route stack)
			_route.push_back(dest);
			while(currPath != start){
				_route.push_back(currPath->returnPosition());
				currPath = currPath->_nodeComponent->returnParent();
			}
			_route.push_back(start->returnPosition());
			_route.shrink_to_fit();
			break;
		}

		openSet.removeEntity(current);
		closedSet.pushBack(current);

		EntityList neighbors = current->_nodeComponent->returnNeighbors();
		EntityListIterator  neighborIter(&neighbors);
		Tile *currNeighbor = static_cast<Tile*>(neighborIter.curr());

		while(currNeighbor != NULL){
			float cost = current->_nodeComponent->_gScore + abs(current->returnPosition().x - currNeighbor->returnPosition().x) + abs(current->returnPosition().y - currNeighbor->returnPosition().y);

			if(openSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				openSet.removeEntity(currNeighbor);
			}

			if(closedSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				closedSet.removeEntity(currNeighbor);
			}
			
			if(!openSet.isMember(currNeighbor) && !closedSet.isMember(currNeighbor)){
				currNeighbor->_nodeComponent->updateFscore(dest, cost);
				currNeighbor->_nodeComponent->setParent(current);
				openSet.pushBack(currNeighbor);
				
			}

			currNeighbor = static_cast<Tile*>(neighborIter.next());
		}
	}

	
}

Tile *PathfindComponent::returnLowestFScore(EntityList *list){
	EntityListIterator tempIter(list);
	Tile *temp = static_cast<Tile*>(tempIter.curr());
	Tile *minFScoreTile = temp;

	while(temp != NULL){
		if (temp->_nodeComponent->_fScore < minFScoreTile->_nodeComponent->_fScore){
			minFScoreTile = temp;
		}
		temp = static_cast<Tile*>(tempIter.next());
	}

	return minFScoreTile;
}


Tile *PathfindComponent::returnTileEntity(sf::Vector2f location){
	EntityListIterator mapIter(_map);
	Tile *entity = static_cast<Tile*>(mapIter.curr());

	while (entity != NULL && entity->returnPosition() != location ){
		entity = static_cast<Tile*>(mapIter.next());
	}
	return entity;
}

float PathfindComponent::getSpeedModifier(MOVESTATE state){
	switch (state){
		case HALTED:
			return 0;
		case CRAWLING:
			return 0.5;
		case WALKING:
			return 1.0;
		case RUNNING:
			return 1.25;
		default:
			return 1.0;
	}
}

