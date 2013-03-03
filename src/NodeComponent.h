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

	NodeComponent(int cost);

	//finds neighboring tiles
	//  - EntityList *map is a linked list of all the tiles present in the map
	//  - Tile *self is the tile we are presently in
	//  - sf::Vector2i mapSize is the size of the map in tiles
	void findNeighbors(EntityList &map, Tile &self, sf::Vector2i mapSize);

	//returns neighboring tiles for evaluation during pathfinding
	EntityList returnNeighbors();

	//sets the parent
	void setParent(Tile &parent);

	//returns the parent tile for backtracing while pathfinding
	Tile *returnParent();

	//updates the gScore and fScore (which depends on gscore) when the node is reevaluated
	void updateGScore(int newGScore);

	//scores for pathfinding
	// fSocore = gScore + hScore
	int _fScore, _gScore, _hScore;

	//cost (this is from a 0 baseline, actual cost of movement is calculated as nextNode.cost - currentNode.cost)
	int _cost;
	
private:

	Tile *_parent;

	EntityList _neighbors;

};