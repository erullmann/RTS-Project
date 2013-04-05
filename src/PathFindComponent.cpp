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
		_position = _route.front();
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
	_map->resetIterator();
	//start tile is closest tile to the entity
	Tile *start = returnTileEntity(sf::Vector2f(round(this->_position.x), round(this->_position.y)));
	Tile *destination = returnTileEntity(dest);
	EntityList closedSet;
	EntityList openSet;
	openSet.pushBack(start);
	start->_nodeComponent->updateFscore(dest, 0);

	while(returnLowestFScore(openSet) != destination){
		Tile *current = returnLowestFScore(openSet);
		closedSet.pushBack(current);

		EntityList neighbors = current->_nodeComponent->returnNeighbors();
		Tile *currNeighbor = static_cast<Tile*>(neighbors.iterateEntites());
		while(currNeighbor != NULL){
			float cost = current->_nodeComponent->_gScore + 1;
			if(openSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				//new path better
				openSet.removeEntity(currNeighbor);
			} 
			if(closedSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				closedSet.removeEntity(currNeighbor);
			}
			if(!closedSet.isMember(currNeighbor) && !openSet.isMember(currNeighbor)){
				currNeighbor->_nodeComponent->updateFscore(dest, cost);
				currNeighbor->_nodeComponent->setParent(current);
				openSet.pushBack(currNeighbor);
			}
		}
		neighbors.resetIterator();
	}

	Tile *currPath = destination;

	//create new route from current position (at end of route stack) to dest (at front of route stack)
	_route.push_back(dest);
	while(currPath != start){
		_route.push_back(currPath->returnPosition());
		currPath = currPath->_nodeComponent->returnParent();
	}
	_route.push_back(start->returnPosition());
	_route.shrink_to_fit();
}

Tile *PathfindComponent::returnLowestFScore(EntityList list){
	Tile *temp = static_cast<Tile*>(list.iterateEntites());
	Tile *minFScoreTile = temp;
	while(temp != NULL){
		if (temp->_nodeComponent->_fScore < minFScoreTile->_nodeComponent->_fScore){
			minFScoreTile = temp;
		}
		temp = static_cast<Tile*>(list.iterateEntites());
	}
	list.resetIterator();
	return minFScoreTile;
}


Tile *PathfindComponent::returnTileEntity(sf::Vector2f location){
	Tile *entity = static_cast<Tile*>(_map->iterateEntites());
	while (entity != NULL && entity->returnPosition() != location ){
		entity = static_cast<Tile*>(_map->iterateEntites());
	}
	_map->resetIterator();
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

