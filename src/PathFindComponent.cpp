#pragma once

#include "PathfindComponent.h"

PathfindComponent::PathfindComponent(sf::Vector2f position, sf::Vector2f heading, EntityList *map, EntityList *entities, float speed){
	_map = map;
	_entities = entities;
	_maxspeed = speed;
	_route.reserve(10);
	_heading = heading;
	_position = position;
	_velocity = sf::Vector2f(0, 0);
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
	_route.front();
}

bool PathfindComponent::atDestination(){
	if (abs(_route.front().x - _position.x) <= 0.1 && abs(_route.front().y - _position.y) <= 0.1){
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
	} else {
		//just keep going to destination
	}

	MobileComponent::update(time);
}


float getSpeedModifier(MOVESTATE state){
	switch (state){
		case HALTED:
			return 0;
		case CRAWLING:
			return 0.5;
		case WALKING:
			return 1.0;
		case RUNNING:
			return 1.25;
	}
}

