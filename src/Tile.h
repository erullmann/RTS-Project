/* Tile.h
   Defines tile class for map and provides drawing functions and information for pathfinding.
*/
#pragma once
#include "SFML\Graphics.hpp"
#include "BaseEntity.h"
#include "EntityType.h"
#include "ResourceManager.h"
#include "NodeComponent.h"
#include "DrawComponent.h"

class NodeComponent;
class DrawComponent;

class Tile: public BaseEntity{
public:

	//Constructor foe tile, sets position, size of tiles (width), type of tile
	Tile(sf::Vector2f position, sf::Vector2i drawSize, sf::RenderWindow &renderWindow, ResourceManager &resourceManager, ENTITYTYPE type, int height); 

	~Tile();

	//draws the tile on the screen
	void draw();
	
	//Returns the entity's type
	ENTITYTYPE returnType();

	//Returns the entity's position
	sf::Vector2f returnPosition();

	//Returns the tile's height
	int returnHeight();

	sf::Vector2f _position;

	int _height;

	ENTITYTYPE _type;

	NodeComponent *_nodeComponent;

	DrawComponent *_drawComponent;

};

