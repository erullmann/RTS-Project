#pragma once
#include "MoverComponent.h"
#include <math.h>

MoverComponent::MoverComponent(BaseEntity* parent, PathfindingService* pathfinder, sf::Vector2i startingPos, MOVEMENTTYPE movementType){
	_pathfinder = pathfinder;
	_position = startingPos;
	_movementType = movementType;
	_parentEntity = parent;
}

void MoverComponent::readMessages(std::vector<msg*>* msgBuffer){
	for(std::vector<msg*>::iterator iter = msgBuffer->begin(); iter != msgBuffer->end(); iter++){
		msg* msg = (*iter);
		_moving = false; //just in case we get no movement messages
		switch (msg->type) {
			case msg::MESSAGETYPE::CURRENTDESTINATION:
				_movingInDirection == false;
				if ((msg->destination.x == _destination.x && msg->destination.y == _destination.y) &&
					(_path->size() >= 1) &&//if there already is a path
					(_path->back() == _position)){
						//destination is same and we are on path
				} else {
					//need to reavaluate movement
					delete _path;
					_path = _pathfinder->findPath(_position, sf::Vector2i(msg->destination.x, msg->destination.y), _movementType);
				}
				break;

			case msg::MESSAGETYPE::CURRENTDIRECTION:
				_movingInDirection = true;
				_proposedDirection = sf::Vector2f(msg->direction.x, msg->direction.y);
				_actualDirection = roundDirection(_proposedDirection);
				break;

			case msg::MESSAGETYPE::CURRENTSTATE:
				if(msg->state.state == MOVING || msg->state.state == MOVING_FAST || msg->state.state == MOVING_SLOW){
					_moving = true;
				} else{
					_moving = false;
				}
				break;

			case msg::MESSAGETYPE::CURRENTSTATS:
				if(msg->stats.moveSpeed != 0)
					_totalMoveTime = 1/msg->stats.moveSpeed;
				break;
			default:
				break;
		}
	}
}

void MoverComponent::update(sf::Time frameTime){
	if(_moving){
		_currMoveTime += frameTime.asSeconds();
		if(_currMoveTime >= _totalMoveTime){
			_currMoveTime = fmod(_currMoveTime, _totalMoveTime); //help avoid lag skips
			if(_movingInDirection){
				_position = _position + _actualDirection;
			} else if(_path->size() > 1) { //if we're not at destination
				_path->pop_back();
				_position = _path->back();
			} else {
				//stay still
			}
		} 
	} else {
		_currMoveTime = 0;//reset movement if we stop, otherwise we'll jump after stoping
	}
}

void MoverComponent::postMessages(std::vector<msg*>* msgBuffer){
	msg* positionMsg = new msg;
	positionMsg->type = msg::MESSAGETYPE::CURRENTPOSITION;
	positionMsg->position.x = _position.x;
	positionMsg->position.y = _position.y;
	msgBuffer->push_back(positionMsg);
}

sf::Vector2i MoverComponent::roundDirection(sf::Vector2f direction){
	int x = 0;
	if(direction.x < 0.7 ){
		x = 1;
	} else if(direction.x < -0.7){
		x = -1;
	}

	int y = 0;
	if(direction.y < 0.7 ){
		y = 1;
	} else if(direction.y < -0.7){
		y = -1;
	}

	return sf::Vector2i(x, y);
}

COMPONENTTYPE BaseComponent::_type = MOVER_COMP;