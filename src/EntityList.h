/* file: EntityList.h
	stuct providing very basic linked list functionality for entities
	General use guidelines for using lists:
		-Lists can and will point to any entity in the game
		-entities can and will be cross listed
		-to avoid double drawing/moveing/ai calculations/etc only ONE central list will be made and sorted for each activity
		-if the list is not to be used for critical activites ^ it should be passed to entities for info ONLY, no manipulating other entities
		-use EntityListIterator to go through lists easily, especially if the the same list is being gone through more then once similtaiusly
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
	//give Iterator access for effiencies sake
	friend class EntityListIterator;

	//starts list
	EntityList();

	//deletes list (but NOT its elements)
	~EntityList();

	//adds entity to back of the list
	//O(1)
	void pushBack(BaseEntity *entity);

	//deletes ELEMENTS of the list, use with caution, elments may be part of other lists
	//O(n)
	void deleteList();

	//Clears list with deleting elements, make sure you're still keeping track of the elements or risk memory leaks
	//O(n)
	void clearList();

	//removes entity from the list
	//O(n)
	void removeEntity(BaseEntity *entity);

	//removes the last element from the list and returns a pointer to its element
	//O(n)
	BaseEntity *popBack();

	//returns pointer to entity at head of the list, returns NULL if empty
	//O(1)
	BaseEntity *head();

	//returns length of list
	//O(1)
	int length();

	//returns true if the given entity is in the list, false otherwise
	//O(n)
	bool isMember(BaseEntity *entity);

private:

	int _length;

	eList *_head;

	eList *_tail;
};

class EntityListIterator {
public:
	
	//starts up empty Iterator
	EntityListIterator();

	//starts up Iterator and sets list as the current list
	EntityListIterator(EntityList *list);

	//assigns list to be the current list (sets one place to begining)
	void assign(EntityList *list);

	//Iterator goes back to begining
	void reset();

	//Goes to and returns next entity in the list
	//If next entity is NULL the Iterator returns NULL and takes no other action
	BaseEntity *next();

	//goes through the list for the next n times, if it reaches the end it loops around and keeps going
	BaseEntity *next(int n);

	//gets the Iterator's current Place (entity its at) in the list
	BaseEntity *getPlace();

	//gets the Iterator's current position (numerical) in the list
	int getPos();

	//returns pointer to the list that the Iterator is currently assigned to
	EntityList *getCurrList();

	//returns true if the the next entity is NULL, false otherwise
	bool atEnd();

private:

	EntityList* _currList;

	eList* _currPlace;

	int _currPos;

};