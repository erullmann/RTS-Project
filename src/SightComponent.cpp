#pragma once

#include "SightComponent.h"

SightComponent::SightComponent(BaseEntity* parent, EntityList* fullEntityList, int sightRadius, sf::Vector2i position){
	_fullEntityList = fullEntityList;
	_sightRadius = sightRadius;
	_visibileEntityList = new EntityList;
	_parentEntity = parent;
	_currentPosition = position;
}

void SightComponent::readMessages(std::vector<msg*>* msgBuffer){
	//find current location

	for(std::vector<msg*>::iterator iter = (*msgBuffer).begin(); iter != (*msgBuffer).end(); ++iter){
		if((*iter)->type == msg::MESSAGETYPE::CURRENTPOSITION){
			_currentPosition = sf::Vector2i((*iter)->position.x, (*iter)->position.y);
		}
	}
}

void SightComponent::update(sf::Time frameTime){
	findVisibleEntites();
}

void SightComponent::postMessages(std::vector<msg*>* msgBuffer){
	msg* sightMsg = new msg;
	sightMsg->type = msg::MESSAGETYPE::VISIBLELIST;
	sightMsg->visible.entityList = _visibileEntityList;
	msgBuffer->push_back(sightMsg);

}

//update for LOS
void SightComponent::findVisibleEntites(){
	_visibileEntityList->clearList();

	EntityListIterator iter(_fullEntityList);
	while(!iter.atEnd()){
		if(iter.curr() != _parentEntity && distance(_currentPosition, iter.curr()->returnPosition()) <= _sightRadius){
			_visibileEntityList->pushBack(iter.curr());
		}
		iter.next();
	}
}

int SightComponent::distance(sf::Vector2i a, sf::Vector2i b){
	int dx = abs(a.x - b.x);
	int dy = abs(a.y - b.y);
	return (dx + dy) + (-0.5)*(std::min(dx, dy));
}

COMPONENTTYPE BaseComponent::_type = SIGHT_COMP;