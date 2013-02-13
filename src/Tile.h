/* Tile.h
   Defines tile class for map and provides drawing functions and information for pathfinding.
*/
#pragma once
#include "SFML\Graphics.hpp"
#include "EntityTypes.h"
#include "ResourceManager.h"


class Tile {
public:

	//Constructor foe tile, sets position, size of tiles (width), type of tile
	Tile(sf::Vector2i position, int drawSize, ENTITYTYPE type, int height); 

	~Tile();
	
	//Generates a map of nearby tiles for pathfinding (and possibly image selection) purposes
	//  - Tile **map is the central map of the game, containing all the tiles
	void findNeighbors(Tile **map);

	//Draws this tile
	//  - sf::RenderWindow &renderWindow is the target window for rendering, should generally be the current window
	//  - int drawLevel is the current height that is being drawn (i.e. objects on the ground get drawn before objects above it)
	void drawSelf(sf::RenderWindow &renderWindow, int drawLevel);

	//Returns a list of pointers to neighboring tiles (<= 8 tiles)
	std::vector<Tile*> returnNeighbors();

	//Returns the entity's type
	ENTITYTYPE returnType();

	//Returns the entity's position
	sf::Vector2i returnPosition();

	//Returns the tile's height
	int returnHeight();

private:

	sf::Vector2i _position;

	sf::Vector2i _drawPosition;

	int _height;

	ENTITYTYPE _type;

	std::vector<Tile*> _neighbors;

};

