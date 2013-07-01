#pragma once

#include "Deer.h"

Deer::Deer(sf::Vector2f position, sf::Vector2f heading, EntityList *map, EntityList *entities, GroupComponent *group, ResourceManager &resourceManager, sf::RenderWindow &renderWindow){
	_drawComponent = new DrawComponent(resourceManager, UNIT_DEER, renderWindow, sf::Vector2i(128, 64), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), sf::Vector2i(0, 0), 1, 1, 1);
	_MovementComponent = new MovementComponent(position, heading, map, entities, 1.0);
	_group = group;
	if(_group != NULL){
		_group->addMember(this);
	}	
}

Deer::~Deer(){
	_group->removeMember(this);
	_drawComponent->~DrawComponent();
	_MovementComponent->~MovementComponent();
}

void Deer::update(sf::Time frameTime){
	_MovementComponent->update(frameTime);
}

void Deer::draw(){
	_drawComponent->drawInGame(_MovementComponent->_position);
}

enum ENTITYTYPE Deer::returnType(){
	return UNIT_DEER;
}

void Deer::setDest(sf::Vector2f dest){
	_MovementComponent->setDestination(dest);
}