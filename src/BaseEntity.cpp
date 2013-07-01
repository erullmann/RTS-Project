#pragma once
#include "BaseEntity.h"


void BaseEntity::update(sf::Time frameTime)
{
	//seperate these out to avoid overlapping message requests
	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
		(*iter)->getMessages(&_msgBuffer);
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

void BaseEntity::destroy()
{
	for(std::vector<BaseComponent*>::iterator iter = _updateBuffer.begin(); iter != _updateBuffer.end(); ++iter){
			(*iter)->destroy();
	}
}


enum ENTITYTYPE BaseEntity::returnType(){
	return _type;
}

void BaseEntity::alterBuffer(std::vector<BaseComponent*>* newBuffer){
	_updateBuffer = *newBuffer;
}

std::vector<BaseComponent*>* BaseEntity::getBuffer(){
	return &_updateBuffer;
}

void BaseEntity::clearMsgBuffer(){
	for(std::vector<msg*>::iterator iter = _msgBuffer.begin(); iter != _msgBuffer.end(); ++iter){
			delete (*iter);
	}
	_msgBuffer.clear();
}