#pragma once
#include "EntityList.h"

//ENTITY LIST CLASS
EntityList::EntityList(){
	_head = NULL;
	_tail = NULL;
	_length = 0;
}

EntityList::~EntityList(){
	eList *curr = _head;
	while (curr != NULL){
		eList *temp = curr;
		curr = curr->nextEntity;
		delete temp;
	}
}

void EntityList::clearList(){
	eList *curr = _head;
	while (curr != NULL){
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

	if (currList != NULL && prevList != NULL){ //not at begining of list
		prevList->nextEntity = currList->nextEntity;
		delete currList;
		_length--;
	} else if(currList != NULL && prevList == NULL){//at begining of list
		_head = currList->nextEntity;
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
	while (currList != NULL && currList->nextEntity != NULL){
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
	EntityListIterator iter(this);
	while (iter.curr() != entity && !iter.atEnd()){
		iter.next();
	}

	if (iter.curr() == entity)
		return true;
	else
		return false;
}


//ENTITY LIST ITERATOR CLASS
EntityListIterator::EntityListIterator(){
	_currList = NULL;
	_currPlace = NULL;
	_currPos = 0;
}

EntityListIterator::EntityListIterator(EntityList* list){
	_currList = list;
	_currPlace = list->_head;
	_currPos = 0;
}

void EntityListIterator::assign(EntityList* list){
	_currList = list;
	_currPlace = list->_head;
	_currPos = 0;
}

void EntityListIterator::reset(){
	_currPos = 0;
	_currPlace = _currList->_head;
}

BaseEntity *EntityListIterator::next(){
	if (!atEnd()){
		_currPlace = _currPlace->nextEntity;
		++_currPos;
		return _currPlace->entity;
	} else {
		return NULL;
	}
}

BaseEntity *EntityListIterator::next(int n){
	int i = 0;
	while (i < n){
		if (!atEnd()){ //while we're not at the end
			next();
		} else { //loop if at end
			reset();
		}
		++i;
	}
	return _currPlace->entity;
}

BaseEntity *EntityListIterator::curr(){
	if (_currPlace == NULL){
		return NULL;
	} else {
		return _currPlace->entity;
	}
}

int EntityListIterator::getPos(){
	return _currPos;
}

EntityList *EntityListIterator::getCurrList(){
	return _currList;
}

bool EntityListIterator::atEnd(){
	if (_currPlace == NULL){
		return true;
	} else {
		return _currPlace->nextEntity == NULL;
	}
}