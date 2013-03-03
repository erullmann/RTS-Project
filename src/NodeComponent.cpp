
#pragma once
#include "NodeComponent.h"

NodeComponent::NodeComponent(int cost){
	_cost = cost;
}

void NodeComponent::findNeighbors(EntityList &map, Tile &self, sf::Vector2i mapSize){
	map.resetIterator();

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

void NodeComponent::updateGScore(int newGScore){
	_gScore = newGScore;
	_fScore = _gScore + _hScore;
}