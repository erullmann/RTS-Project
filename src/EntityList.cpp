#pragma once
#include "EntityList.h"

EntityList::EntityList(){
	_head = NULL;
	_tail = NULL;
	_currIterator = NULL;
	_length = 0;
}

EntityList::~EntityList(){
	eList *curr = _head;
	while (curr->nextEntity != NULL){
		eList *temp = curr;
		curr = curr->nextEntity;
		delete temp;
	}
}

void EntityList::pushBack(BaseEntity *entity){
	if(_head == NULL){
		_head = new eList;
		_head->entity = entity;
		_head->nextEntity = NULL;
		_tail = _head;
		_currIterator = _head;
	} else{
		_tail->nextEntity = new eList;
		_tail = _tail->nextEntity;
		_tail->entity = entity;
		_tail->nextEntity = NULL;
	}
	_length++;
}

void EntityList::removeEntity(BaseEntity *entity){
	eList *prevList = NULL;
	eList *currList = _head;
	while (currList != NULL && currList->entity != entity){
		prevList = currList;
		currList = currList->nextEntity;
	}

	if (currList != NULL){
		prevList->nextEntity = currList->nextEntity;
		delete currList;
		_length--;
	} else{
		//not in list, do nothing
	}
}

void EntityList::deleteList(){
	while (_head != NULL){
		eList *temp = _head;
		_head->entity->destroy();
		_head = _head->nextEntity;
		delete temp;
	}
	_length = 0;
}

BaseEntity *EntityList::popBack(){
	eList *prevList = NULL;
	eList *currList = _head;
	while (currList->nextEntity != NULL){
		prevList = currList;
		currList = currList->nextEntity;
	}

	if (prevList != NULL){
		prevList->nextEntity = NULL;
	} else{
		_head = NULL;
	}
	_tail = prevList;
	BaseEntity *temp = currList->entity;
	delete currList;
	_length--;
	return temp;
}

BaseEntity *EntityList::head(){
	if (_head != NULL)
		return _head->entity;
	else
		return NULL;
}

int EntityList::length(){
	return _length;
}

bool EntityList::isMember(BaseEntity *entity){
	BaseEntity *x = iterateEntites();
	while(x != NULL){
		if (x == entity)
			return true;
		else
			x = iterateEntites();
	}
	resetIterator();
	return false;
}

BaseEntity *EntityList::iterateEntites(){
	BaseEntity *temp;
	if (_currIterator == NULL){
		temp = NULL;
		_currIterator = _head;
	} else{
		temp = _currIterator->entity;
		_currIterator = _currIterator->nextEntity;
	}
	return temp;
}

void EntityList::resetIterator(){
	_currIterator = _head;
}