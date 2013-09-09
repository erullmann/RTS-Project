#pragma once

#include "BaseComponent.h"

//most of these classes should be replaced by others

BaseComponent::BaseComponent(){
	_type = BASE_COMP;
}

void BaseComponent::readMessages(std::vector<msg*>* msgBuffer){
	//do nothing
}

void BaseComponent::update(sf::Time frameTime){
	//do nothing
}

void BaseComponent::postMessages(std::vector<msg*>* msgBuffer){
	//do nothing
}

void BaseComponent::destroy(){
	//do nothing
}

COMPONENTTYPE BaseComponent::returnType(){
	return _type;
}

COMPONENTTYPE BaseComponent::_type = BASE_COMP;