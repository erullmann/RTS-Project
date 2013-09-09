/* EntityTypes.h
   Defines the various statuses for use across most classes
   */
#pragma once

enum GENERICTYPE{
	CREATURE,
	PLANT,
	INANIMATE
};

//centeral list of all enity types (might want to change this if dymanic entity loading is implemented)
enum ENTITYTYPE{
	BASE_TYPE,
	TILE_OCEAN,
	TILE_GRASS,
	TILE_DESERT,
	TILE_ROCK,
	TILE_WOOD,
	ANIMAL_DEER,
	ANIMAL_WOLF,
	PLANT_GRASS
};

//all the ways those little critters can move
enum MOVEMENTTYPE{
	STATIONARY,
	WALKER,
	SWIMMER,
	FLYER,
	AMPHIBIOUS
};

//Component types
enum COMPONENTTYPE{
	BASE_COMP,
	MOVER_COMP,
	BODY_COMP,
	SIGHT_COMP,
	FEAR_COMP
};

enum SOUNDTYPE{
	NOISE,
	STAY_AWAY,
	WANT_MATE,
	HELP_ME,
};

enum SMELLTYPE{
	PISS,
	SHIT,
	HEAT,//mating heat
	BLOOD,
	DEATH,
	POLLEN
};

enum ANIMALSTATE{
	RESTING,
	SLEEPING,
	STUNNED,
	UNCONSCIOUS,
	DRINKING,
	FEEDING,
	MOVING_SLOW,
	MOVING,
	MOVING_FAST,
	ATTCKING,
	MATING,
	CALLING
};

enum RECOMMONDATION{
	FEED,
	FLEE,
	FIGHT,
	MATE,
	HUNT,
	REST
};

enum RELATION{
	UNKNOWN,
	MATE,
	FAMILY,
	ALLY,
	NEUTRAL,
	FOE,
	FOOD
};