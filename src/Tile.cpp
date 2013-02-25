#pragma once
#include "Tile.h"

Tile::Tile(sf::Vector2i position, sf::Vector2i drawSize, sf::RenderWindow &renderWindow, ResourceManager *resourceManager, ENTITYTYPE type, int height){
	//might want to change the cost calculation later
	NodeComponent nodeComponent(height);
	_nodeComponent = &nodeComponent;

	DrawComponent drawComponent(resourceManager, type, renderWindow, drawSize, sf::Vector2i(0,0), sf::Vector2i(0,0), sf::Vector2i(0,0), sf::Vector2i(0,0), 0, 0, 0);
	_drawComponent = &drawComponent;

	_type = type;
	_height = height;
	_position = position;
}

Tile::~Tile(){
	_drawComponent->~DrawComponent();
	_nodeComponent->~NodeComponent();
}

void Tile::draw(){
	_drawComponent->drawInGame(sf::Vector2f(_position));
}

ENTITYTYPE Tile::returnType(){
	return _type;
}

sf::Vector2i Tile::returnPosition(){
	return _position;
}

int Tile::returnHeight(){
	return _height;
}