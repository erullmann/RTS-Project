#pragma once
/*Message.h
 Implements the message class for intra-entity and inter-entity messaging 
 This sort of message type pattern is based on the SFML event system found in Event.hpp
*/
#include "BaseEntity.h"
#include "Types.h"

class msg {
public: 

	//EXTRNAL INFO
	struct SoundEvent {
		float intensity; //1-0 with 1 being load sound right next to you
		float x; //normalized direction of the sound
		float y;
		enum SOUNDTYPE type; //type of sound (mating call, grow, etc.)
	};

	struct SmellEvent {
		float intensity; //how old the smell is and how far from the source it is
		float x; //normalized direction of the smell
		float y;
		enum SMELLTYPE type; //piss, blood, whatever
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
		int amount; //how many calories to add or subtract (negative to subtract)
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
		enum ANIMALSTATE state; //state of creature, useful for drawing and such
	};

	struct CurrentDirection {
		float x; //general (normailized) direction of movement (no particular entity target)
		float y;
	};

	struct CurrentDestination {
		float x; //exact location where the creature wants to go, generaly food or target is there
		float y;
	};

	struct CurrentTarget {
		BaseEntity * target; //creature or item to target for attacks or for getting food or for mating
	};

	//NON-LOS STUFF
	struct AvoidNote {
		float x;//direction not to gotowards
		float y;
		float breadth; //1-0 how much to avoid it on either side (1: don't move towards 90deg offset, 0:don't go directly towards it)
		float intensity; //1-0 how much to avoid going towards it (1: never-ever go to it, 0.5: go a few steps towards it, 0: walk right up to it)
	};

	struct ApprochNote {
		float x; //direction to go towards
		float y;
		float breadth; //1-0 how much to approch it on either side (1: move towards 90deg offset, 0:go directly towards it)
		float intensity; //1-0 how much to go towards it (1: go in this direction a lot, 0.5: go a few steps towards it, 0: don't care about it)
	};

	//STUFF IN LOS
	//AI will generally work by picking the highest ranked recomend action, chose the best food/prey/mate note (after having rejected or enhanced them based on appoch or avoid) and perform the relevent action
	//if nothing is really avaible it will head towards apporch directions, otherwise it will rest
	struct FoodNote {
		BaseEntity* foodsource; //object that can be eaten (if animal, it should be dead)
		int rank; //rank of acceptability of food, based on location, amount, etc; 1 is highest
	};

	struct RecommendFeed {//put food finding first
		int priority; //1-10, 1 is most important
	};

	struct PreyNote {
		BaseEntity* prey; //living animal that could be eaten
		int rank; //ease of access for food, based on creature health, location, relative speed, etc; 1 is highest
	};

	struct RecommendHunt { //will chase highest rank prey and attack it when adjacent
		int priority; //1-10, 1 is most important
	};

	struct PredatorNote { //can be acompnied be avoid notice
		BaseEntity* predator;
		int rank; //rank out of all nearby predators (note this is relational, not absolute, use other messages to recommend actions)
	};

	struct RecommendFlee {
		int priority; //1-10, flees from predators and avoid areas and towards approch areas
	};

	struct RecommendAttack {//will be against highest rank, adjacent predator, otherwise goto closest predetor
		int priority; //1-10, 1 is most important
	};

	struct MateNote {
		BaseEntity* mate; //potential mate
		int rank; //rank based on mate health, closeness, etc.; 1 is highest
	};

	struct RecomendMate {//goto and mate with highest rank mate
		int priority; //1-10, 1 is most important
	};

	struct RecommendRest {//don't do anything (useful for saving energy or growing)
		int priority; //1-10, 1 is most important
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
		AVOIDNOTE,
		APPROCHNOTE,
		FOODNOTE,
		PREYNOTE,
		PREDATORNOTE,
		MATENOTE,
		RECOMMENDFEED,
		RECOMMENDHUNT,
		RECOMMENDFLEE,
		RECOMMENDATTCK,
		RECOMMENDMATE,
		RECOMMENDREST,

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
		AvoidNote			avoid;
		ApprochNote			approch;
		FoodNote			food;
		PreyNote			prey;
		PredatorNote		predator;
		MateNote			mate;
		RecommendFeed		feed;
		RecommendHunt		hunt;
		RecommendFlee		flee;
		RecommendAttack		attack;
		RecomendMate		sex;
		RecommendRest		rest;
	};

};