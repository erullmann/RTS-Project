#pragma once
#include "Tile.h"

Tile::Tile(sf::Vector2f position, sf::Vector2i drawSize, sf::RenderWindow &renderWindow, ResourceManager &resourceManager, ENTITYTYPE type, int height){
	_type = type;
	_height = height;
	_position = position;	
	//might want to change the cost calculation later
	_nodeComponent = new NodeComponent(this);
	sf::Vector2i zero(0,0);
	_drawComponent = new DrawComponent(resourceManager, type, renderWindow, drawSize, zero, zero, zero, zero, 0, 0, 0);
}

Tile::~Tile(){
	delete _drawComponent;
	delete _nodeComponent;
}

void Tile::draw(){
	_drawComponent->drawInGame(sf::Vector2f(_position));
}

ENTITYTYPE Tile::returnType(){
	return _type;
}

sf::Vector2f Tile::returnPosition(){
	return _position;
}

int Tile::returnHeight(){
	return _height;
}