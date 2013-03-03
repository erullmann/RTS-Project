/* file: EntityList.h
	stuct providing very basic linked list functionality for entities
	General use guidelines for using lists:
		-Lists can and will point to any entity in the game
		-entities can and will be cross listed
		-to avoid double drawing/moveing/ai calculations/etc only ONE central list will be made and sorted for each activity
		-if the list is not to be used for critical activites ^ it should be passed to entities for info ONLY, no manipulating other entities
*/
#pragma once
#include "BaseEntity.h"

//nextEntity list is NULL (last element) or an EntityList
struct eList{
	BaseEntity *entity;
	eList *nextEntity;
};

class EntityList{
public:
	//starts list
	EntityList();

	//deletes list (but NOT its elements)
	~EntityList();

	//adds entity to back of the list
	void pushBack(BaseEntity *entity);

	//deletes ELEMENTS of the list, use with caution, elments may be part of other lists
	void deleteList();

	//removes the last element from the list and returns a pointer to its element
	BaseEntity *popBack();

	//returns pointer to entity at head of the list, returns NULL if empty
	BaseEntity *head();

	//returns pointer to entity at end of the list, returns NULL if empty
	BaseEntity *tail();

	int length();

	//rentuns entity pointer at the next place in the list, resets itself when it returns NULL
	BaseEntity *iterateEntites();

	//resets the Iterator to the begging of the list
	void resetIterator();

private:
	int _length;

	eList *_currIterator;

	eList *_head;

	eList *_tail;
};