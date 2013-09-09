#pragma once
/*Message.h
 Implements the message class for intra-entity and inter-entity messaging 
 This sort of message type pattern is based on the SFML event system found in Event.hpp
*/
#include "EntityList.h"
#include "Types.h"

class msg {
public: 

	//EXTRNAL INFO
	struct SoundEvent {
		float intensity; //1-0 with 1 being load sound right next to you
		float x; //normalized direction of the sound
		float y;
		SOUNDTYPE type; //type of sound (mating call, growl, etc.)
		ENTITYTYPE source; //source of sound
	};

	struct SmellEvent {
		float intensity; //how old the smell is and how far from the source it is
		float x; //normalized direction of the smell
		float y;
		SMELLTYPE type; //piss, blood, whatever
		ENTITYTYPE source; //source of smell
	};

	struct DamageEvent {
		float force; //newtons (kg*m/s^2)
	};

	//STATUS UPDATES
	struct CalorieCount {
		int amount; //how many calories the animal has
	};

	struct CalorieChange {
		bool isGiving; //true if calories are being given
		int amount; //how many calories to add or subtract
	};

	struct CurrentPosition {
		float x;
		float y;
	};

	struct CurrentStats {
		float moveSpeed; // m/s (one tile is 1 m^2)
		float attackSpeed; // sec (seconds between attacks)
		float strength; // newtons (kg*m/s^2)
		float mass; //kg
	};

	struct CurrentState {
		ANIMALSTATE state; //state of creature, useful for drawing and such
	};

	struct CurrentDirection {
		float x; //general (normailized) direction of movement (no particular entity target)
		float y;
	};

	struct CurrentDestination {
		int x; //exact location where the creature wants to go, generaly food or target is there
		int y;
	};

	struct CurrentTarget {
		BaseEntity * target; //creature or item to target for attacks or for getting food or for mating
	};


	//AI will generally work by picking the highest ranked recomend action, chose the best food/prey/mate note (after having rejected or enhanced them based on appoch or avoid) and perform the relevent action
	//if nothing is really avaible it will head towards apporch directions, otherwise it will rest

	//NON-LOS STUFF
	//notes based on sounds/smells that indicate wheather to go towards or away from them
	struct InvisibileList { //make list thing
		float x;//direction of unknown
		float y;
		float intensity; //1-0 how strong it is, 1 is stongest
		RELATION relation; //what we think is at the end of the rainbow (foe, friend, etc)
		ENTITYTYPE source; //source of note
	};

	//STUFF IN LOS
	//Entity notes of nearby creatures and plants of interest
	struct VisibileList {
		EntityList* entityList; //plants, animals, whatever in order of distance
	};

	//RECCOMMENDATIONS
	//Request creature control
	struct RequestAffinity {
		float priority; //1-0, 1 is most important
		COMPONENTTYPE type;
	};

	//central AI grants affinity to this component
	struct GrantAffinity {
		COMPONENTTYPE type;
	};
	
	enum MESSAGETYPE {
		SOUNDEVENT,
		SMELLEVENT,
		DAMAGEEVENT,
		CALORIECOUNT,
		CALORIECHANGE,
		CURRENTPOSITION,
		CURRENTDIRECTION,
		CURRENTDESTINATION,
		CURRENTTARGET,
		CURRENTSTATS,
		CURRENTSTATE,
		INVISIBLELIST,
		VISIBLELIST,
		REQUESTAFFINITY,
		GRANTAFFINITY,

		COUNT //stays last
	};

	//member data

	MESSAGETYPE type;

	union {
		SoundEvent			sound;
		SmellEvent			smell;
		DamageEvent			damage;
		CalorieCount		count;
		CalorieChange		change;
		CurrentPosition		position;
		CurrentDirection	direction;
		CurrentDestination	destination;
		CurrentTarget		target;
		CurrentStats		stats;
		CurrentState		state;
		InvisibileList		invisible;
		VisibileList		visible;
		RequestAffinity		request;
		GrantAffinity		grant;
	};

};