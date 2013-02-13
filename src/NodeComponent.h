/* NodeComponent.h
   Provides node functionality for pathfinding to tiles and possibly AI waypoints
*/
#pragma once
#include "SFML\System.hpp"
#include "Tile.h"

class NodeComponent{
public:

	NodeComponent(int cost);

	//finds neighboring tiles
	//  - Tile **map is a array of all the tiles present in the map
	//  - Tile *self is the tile we are presently in
	//  - sf::Vector2i mapSize is the size of the map in tiles
	void findNeighbors(Tile **map, Tile *self, sf::Vector2i mapSize);

	//returns neighboring tiles for evaluation during pathfinding
	std::vector<Tile*> returnNeighbors();

	//sets the parent
	void setParent(Tile *parent);

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

	Tile *parent;

	std::vector<Tile*> neighbors;

};