//SightComponenet.h
//Sight Component Class
//Finds all enties within line of sight and posts them in a list in order by distance

#pragma once
#include "BaseComponent.h"
#include "EntityList.h"

class SightComponent : public BaseComponent {
public:

	//fullEntityList is the list of all entites in the game
	//sightRadius is the radius of the creature's line of sight (might make this dynamic later)
	SightComponent(BaseEntity* parent, EntityList* fullEntityList, int sightRadius, sf::Vector2i position);

	//find our location
	void readMessages(std::vector<msg*>* msgBuffer);

	//looks for entites
	void update(sf::Time frameTime);

	//posts list
	void postMessages(std::vector<msg*>* msgBuffer);

private:

	//list of close enties
	EntityList* _visibileEntityList;

	EntityList* _fullEntityList;

	//finds visible entites (entities within ~<20 tiles)
	void findVisibleEntites();

	int distance(sf::Vector2i a, sf::Vector2i b);

	int _sightRadius;

	sf::Vector2i _currentPosition;

};