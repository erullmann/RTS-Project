/* NodeComponent.h
   Provides node functionality for pathfinding to tiles and possibly AI waypoints
*/
#pragma once
#include "SFML\System.hpp"
#include "EntityList.h"
#include "Tile.h"

class Tile;

class NodeComponent{
public:

	NodeComponent(Tile *self);

	//finds neighboring tiles
	//  - EntityList *map is a linked list of all the tiles present in the map
	//  - Tile *self is the tile we are presently in
	//  - sf::Vector2i mapSize is the size of the map in tiles
	void findNeighbors(EntityList &map, Tile &self, sf::Vector2i mapSize);

	//returns neighboring tiles for evaluation during pathfinding
	EntityList returnNeighbors();

	//sets the parent
	void setParent(Tile *parent);

	//returns the parent tile for backtracing while pathfinding
	Tile *returnParent();	

	//recalulates and returns new fscore
	float updateFscore(sf::Vector2f dest, float gscore);

	//scores for pathfinding
	// fScore = gScore + hScore
	float _fScore, _gScore, _hScore, _dScore;
	
private:

	Tile *_parent;

	EntityList _neighbors;

	sf::Vector2f _position;

};