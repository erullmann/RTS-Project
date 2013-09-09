//FearComponenet.h
//assesses nearby creatures, compares them to oneself and dicides weather to flee and the direction to do so

#pragma once
#include "BaseComponent.h"

//an easily adjustable weight on the assment of threats
//adjust to make animals more or less skitish
#define SECURITYWEIGHTING 1.0

class FearComponent : public BaseComponent {
public:

	//find visibile entites
	//checks if we have affinity
	//check our own stats
	void readMessages(std::vector<msg*>* msgBuffer);

	//assesses weather other entites are a threat: dicides on affinty recommendation
	// if we have affinity figure direction to run
	void update(sf::Time frameTime);

	//posts affinity request
	//if has affinity:
	//  posts destination/direction
	void postMessages(std::vector<msg*>* msgBuffer);

private:

	bool _hasAffinity;
	float _prevAffinityRequest;//used to try and keep affinity
	float _currentAffinityRequest;

	EntityList* _visibleEntityList;

	//stats
	float _moveSpeed; // m/s (one tile is 1 m^2)
	float _attackSpeed; // sec (seconds between attacks)
	float _strength; // newtons (kg*m/s^2)
	float _mass; //kg
	sf::Vector2i _position;

	//8 sectors around the creature
	//add and subtract securtity from each sector based on threats
	//recommend affinity based on these assesments
	//we do this because we can only dicide to go in one of eight directions extra detail dosen't help
	float _sectorSecurity[8];

	//sector with lowest threat
	int _lowestThreatSector;

	//calculate the individual threat of an entity
	//negative are potective elements like allies
	float calculateThreat(BaseEntity* entity);

	//returns quadrent relative to us
	//starts at 0 at the top and goes clockwise
	int calculateSector(BaseEntity* entity);

};