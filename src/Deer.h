#pragma once
//file Deer.h
//defines Deer class

#include "DrawComponent.h"
#include "MovementComponent.h"
#include "GroupComponent.h"

class Deer: public BaseEntity{
public:
	Deer(sf::Vector2f position, sf::Vector2f heading, EntityList *map, EntityList *entities, GroupComponent *group, ResourceManager &resourceManager, sf::RenderWindow &renderWindow);

	~Deer();

	void update(sf::Time frameTime);

	void draw();

	//testing code, get rid of me
	void setDest(sf::Vector2f dest);

	ENTITYTYPE returnType();

	DrawComponent *_drawComponent;

	MovementComponent *_MovementComponent;

	GroupComponent *_group;
};