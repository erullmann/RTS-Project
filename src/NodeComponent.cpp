
#pragma once
#include "NodeComponent.h"

NodeComponent::NodeComponent(int cost){
	_cost = cost;
}

void NodeComponent::findNeighbors(Tile **map, Tile *self, sf::Vector2i mapSize){
	sf::Vector2i selfPos = self->returnPosition();
	for (int i = -1; i < 1; i++){
		for (int j = -1; j < 1; j++){
			if ((selfPos.x + i) >= 0 && (selfPos.x + i) < mapSize.x && //potential neighbor is not out of bounds
				(selfPos.y + i) >= 0 && (selfPos.y + i) < mapSize.y &&
				(i != 0 && j != 0)){ //and is not ourselves
					neighbors.push_back(&map[i][j]); //add it to our list of neighbors
			}
		}
	}
}

std::vector<Tile*> NodeComponent::returnNeighbors(){
	return neighbors;
}

void NodeComponent::updateGScore(int newGScore){
	_gScore = newGScore;
	_fScore = _gScore + _hScore;
}