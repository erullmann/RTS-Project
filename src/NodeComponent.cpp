
#pragma once
#include "NodeComponent.h"

NodeComponent::NodeComponent(Tile *self){
	_position = self->returnPosition();
}

void NodeComponent::findNeighbors(EntityList &map, Tile &self, sf::Vector2i mapSize){
	map.resetIterator();
	//fix iterator
	for (int i = 0; i < mapSize.x * mapSize.y; i++){
		BaseEntity *temp = map.iterateEntites();
		if(temp->returnPosition() != self.returnPosition()){
			if (temp->returnPosition().x - self.returnPosition().x < 1 && temp->returnPosition().x - self.returnPosition().x > -1){
				if (temp->returnPosition().y - self.returnPosition().y < 1 && temp->returnPosition().y - self.returnPosition().y > -1){
					_neighbors.pushBack(temp);
				}
			}
		}
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