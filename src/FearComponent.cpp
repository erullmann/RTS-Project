#pragma once
#include "FearComponent.h"

void FearComponent::readMessages(std::vector<msg*>* msgBuffer){
	//find our stats, other entity locations and if we have affinity

	for(std::vector<msg*>::iterator iter = (*msgBuffer).begin(); iter != (*msgBuffer).end(); ++iter){
		switch((*iter)->type){
		case msg::MESSAGETYPE::CURRENTSTATS:
			_moveSpeed = (*iter)->stats.moveSpeed;
			_attackSpeed = (*iter)->stats.attackSpeed;
			_strength = (*iter)->stats.strength;
			_mass = (*iter)->stats.mass;
			break;

		case msg::MESSAGETYPE::CURRENTPOSITION:
			_position.x = (*iter)->position.x;
			_position.y = (*iter)->position.y;
			break;

		case msg::MESSAGETYPE::VISIBLELIST:
			_visibleEntityList = (*iter)->visible.entityList;
			break;

		case msg::MESSAGETYPE::GRANTAFFINITY:
			if((*iter)->grant.type == this->returnType()){
				_hasAffinity = true;
			} else {
				_hasAffinity = false;
			}
			break;
		};
	}
}

void FearComponent::update(sf::Time frameTime){
	//visible entities
	EntityListIterator iter(_visibleEntityList);

	for(int i = 0; i < 8; i++)
		_sectorSecurity[i] = 0;

	while(!iter.atEnd()){
		
		_sectorSecurity[calculateSector(iter.curr())] += calculateThreat(iter.curr());
		
		iter.next();
	}

	//add invisible entity calc here

	//affinity

	_currentAffinityRequest = (_prevAffinityRequest + _currentAffinityRequest)/2;
	_prevAffinityRequest = _currentAffinityRequest;

	if(_hasAffinity){
		_lowestThreatSector = 0;

		for(int i = 0; i < 8; i++)
			if(_sectorSecurity[i] < _sectorSecurity[_lowestThreatSector])
				_lowestThreatSector = i;
	}
}

void FearComponent::postMessages(std::vector<msg*>* msgBuffer){
	msg* affinityMsg = new msg;
	affinityMsg->type = msg::MESSAGETYPE::REQUESTAFFINITY;
	affinityMsg->request.priority = _currentAffinityRequest;
	affinityMsg->request.type = this->returnType();
	(*msgBuffer).push_back(affinityMsg);

	if(_hasAffinity){
		sf::Vector2i sector(0, 0);
		switch(_lowestThreatSector){
		case 0:
			sector.x = 0;
			sector.y = 1;
			break;
		case 1:
			sector.x = 1;
			sector.y = 1;
			break;
		case 2:
			sector.x = 1;
			sector.y = 0;
			break;
		case 3:
			sector.x = 1;
			sector.y = -1;
			break;
		case 4:
			sector.x = 0;
			sector.y = -1;
			break;
		case 5:
			sector.x = -1;
			sector.y = -1;
			break;
		case 6:
			sector.x = -1;
			sector.y = 0;
			break;
		case 7:
			sector.x = -1;
			sector.y = 1;
			break;

		};

		msg* directionMsg = new msg;
		directionMsg->type = msg::MESSAGETYPE::CURRENTDIRECTION;
		directionMsg->direction.x = sector.x;
		directionMsg->direction.y = sector.y;
		(*msgBuffer).push_back(directionMsg);
	}
}

float FearComponent::calculateThreat(BaseEntity* entity){

	std::vector<msg*>* msgBuffer = entity->getMessageBuffer();

	for(std::vector<msg*>::iterator iter = (*msgBuffer).begin(); iter != (*msgBuffer).end(); ++iter){
		switch((*iter)->type){
		case msg::MESSAGETYPE::CURRENTSTATS:
			float entityMoveSpeed = (*iter)->stats.moveSpeed;
			float entityAttackSpeed = (*iter)->stats.attackSpeed;
			float entityStrength = (*iter)->stats.strength;
			float entityMass = (*iter)->stats.mass;
			break;

		case msg::MESSAGETYPE::CURRENTPOSITION:
			sf::Vector2i entityPosition;
			entityPosition.x = (*iter)->position.x;
			entityPosition.y = (*iter)->position.y;
			break;
		};
	}



}

int FearComponent::calculateSector(BaseEntity* entity){

	std::vector<msg*>* msgBuffer = entity->getMessageBuffer();
	sf::Vector2i entityLocation(0, 0);

	for(std::vector<msg*>::iterator iter = (*msgBuffer).begin(); iter != (*msgBuffer).end(); ++iter){
		switch((*iter)->type){
		case msg::MESSAGETYPE::CURRENTPOSITION:
			entityLocation.x = (*iter)->position.x;
			entityLocation.y = (*iter)->position.y;
			break;
		};
	}

	sf::Vector2i difference(_position.x - entityLocation.x, _position.y - entityLocation.y);
	float length = sqrt((difference.x * difference.x) + (difference.y * difference.y));
	difference.x = difference.x/length;
	difference.y = difference.y/length;

	int x = 0;
	if(difference.x < 0.7 ){
		x = 1;
	} else if(difference.x < -0.7){
		x = -1;
	}

	int y = 0;
	if(difference.y < 0.7 ){
		y = 1;
	} else if(difference.y < -0.7){
		y = -1;
	}

	if(x == 1){
		if(y == 1){
			return 1;
		} else if (y == 0) {
			return 2;
		} else if (y == -1) {
			return 3;
		}
	} else if (x == 0) {
		if(y == 1){
			return 0;
		}
		else if (y == -1) {
			return 4;
		}
	} else if (x == -1) {
		if(y == 1){
			return 7;
		} else if (y == 0) {
			return 6;
		} else if (y == -1) {
			return 5;
		}
	}
}

COMPONENTTYPE BaseComponent::_type = FEAR_COMP;