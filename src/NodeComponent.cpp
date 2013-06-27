
#pragma once
#include "NodeComponent.h"

NodeComponent::NodeComponent(Tile *self){
	_position = self->returnPosition();
	_gScore = 0;
	_fScore = 0;
	_hScore = 0;
}

void NodeComponent::findNeighbors(EntityList &map, Tile &self, sf::Vector2i mapSize){
	EntityListIterator mapIter(&map);
	BaseEntity *temp = mapIter.curr();

	for (int i = 0; i < mapSize.x * mapSize.y; i++){
		if(temp->returnPosition() != self.returnPosition()){
			if (temp->returnPosition().x - self.returnPosition().x < 2 && temp->returnPosition().x - self.returnPosition().x > -2){
				if (temp->returnPosition().y - self.returnPosition().y < 2 && temp->returnPosition().y - self.returnPosition().y > -2){
					_neighbors.pushBack(temp);
				}
			}
		}

		temp = mapIter.next();
	}
}

EntityList NodeComponent::returnNeighbors(){
	return _neighbors;
}

float NodeComponent::updateFscore(sf::Vector2f dest, float gScore){
	_gScore = gScore;
	_hScore = abs(dest.x - _position.x) + abs(dest.y - _position.y);
	_fScore = _gScore + _hScore;
	return _fScore;
}

void NodeComponent::setParent(Tile *parent){
	_parent = parent;
}

Tile *NodeComponent::returnParent(){
	return _parent;
}