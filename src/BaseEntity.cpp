#pragma once
#include "BaseEntity.h"


void BaseEntity::update(sf::Time frameTime)
{
	//seperate these out to avoid overlapping message requests
	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
		(*iter)->readMessages(&_msgBuffer);
	}

	clearMsgBuffer();

	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
			(*iter)->update(frameTime);
	}

	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
			(*iter)->postMessages(&_msgBuffer);
	}

	_msgBuffer.shrink_to_fit();

}
void BaseEntity::draw()
{
	_drawComponent->draw();
}

void BaseEntity::postMessage(msg* message){
	_msgBuffer.push_back(message);
}

std::vector<msg*>* BaseEntity::getMessageBuffer(){
	return &_msgBuffer;
}

void BaseEntity::destroy()
{
	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
			(*iter)->destroy();
	}
}


ENTITYTYPE BaseEntity::returnType(){
	return _type;
}

sf::Vector2i BaseEntity::returnPosition(){
	for(std::vector<msg*>::iterator iter = _msgBuffer.begin(); iter != _msgBuffer.end(); ++iter){
		if((*iter)->type == msg::MESSAGETYPE::CURRENTPOSITION){
			return sf::Vector2i((*iter)->position.x, (*iter)->position.y);
		}
	}
	return sf::Vector2i(0,0);
}

void BaseEntity::alterComponentList(std::vector<BaseComponent*> newBuffer){
	_updateBuffer = newBuffer;
}

std::vector<BaseComponent*>* BaseEntity::getComponentList(){
	return &_updateBuffer;
}

void BaseEntity::clearMsgBuffer(){
	for(std::vector<msg*>::iterator iter = _msgBuffer.begin(); iter != _msgBuffer.end(); ++iter){
			delete (*iter);
	}
	_msgBuffer.clear();
}