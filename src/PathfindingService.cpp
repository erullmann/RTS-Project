#pragma once

#include "PathfindingService.h"

//utility function that rounds off numbers
float round(float x){
	return floor(x + 0.5);
}

PathfindingService::PathfindingService(EntityList *map){
	_map = map;
}

//we can add filter for movement types later (i.e. filter neighbors for water tiles and such)
std::vector<sf::Vector2i>* PathfindingService::findPath(sf::Vector2i start, sf::Vector2i end, enum MOVEMENTTYPE moveType){
	//make new route
	std::vector<sf::Vector2i>* route = new std::vector<sf::Vector2i>;

	//start tile is closest tile to the entity
	Tile *startEntity = returnTileEntity(start);
	Tile *destEntity = returnTileEntity(end);
	EntityList closedSet;
	EntityListIterator closedIter(&closedSet);

	EntityList openSet;
	EntityListIterator openIter(&openSet);
	openSet.pushBack(startEntity);
	startEntity->_nodeComponent->updateFscore(sf::Vector2f(end.x, end.y), 0);

	while(openSet.length() != 0){
		Tile *current = returnLowestFScore(&openSet);

		if (current == destEntity){
			Tile *currPath = destEntity;

			//create new route from current position (at front of route stack) to dest (at end of route stack)
			route->push_back(end);

			while(currPath != startEntity){
				route->push_back(sf::Vector2i(currPath->returnPosition().x, currPath->returnPosition().y));
				currPath = currPath->_nodeComponent->returnParent();
			}
			route->push_back(start);
			route->shrink_to_fit();
			break;
		}

		openSet.removeEntity(current);
		closedSet.pushBack(current);

		EntityList neighbors = current->_nodeComponent->returnNeighbors();
		EntityListIterator  neighborIter(&neighbors);
		Tile *currNeighbor = static_cast<Tile*>(neighborIter.curr());

		while(currNeighbor != NULL){
			float cost = current->_nodeComponent->_gScore + 1;

			if(openSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				openSet.removeEntity(currNeighbor);
			}

			if(closedSet.isMember(currNeighbor) && cost < currNeighbor->_nodeComponent->_gScore){
				closedSet.removeEntity(currNeighbor);
			}
			
			if(!openSet.isMember(currNeighbor) && !closedSet.isMember(currNeighbor)){
				currNeighbor->_nodeComponent->updateFscore(sf::Vector2f(end.x, end.y), cost);
				currNeighbor->_nodeComponent->setParent(current);
				openSet.pushBack(currNeighbor);
				
			}
			
			currNeighbor = static_cast<Tile*>(neighborIter.next());
		}
		
	}

	return route;
}

Tile *PathfindingService::returnLowestFScore(EntityList *list){
	EntityListIterator tempIter(list);
	Tile *temp = static_cast<Tile*>(tempIter.curr());
	Tile *minFScoreTile = temp;

	while(temp != NULL){
		if (temp->_nodeComponent->_fScore < minFScoreTile->_nodeComponent->_fScore){
			minFScoreTile = temp;
		}
		temp = static_cast<Tile*>(tempIter.next());
	}

	return minFScoreTile;
}


Tile *PathfindingService::returnTileEntity(sf::Vector2i location){
	EntityListIterator mapIter(_map);
	Tile *entity = static_cast<Tile*>(mapIter.curr());

	while (entity != NULL && entity->returnPosition().x != location.x && entity->returnPosition().y != location.y ){
		entity = static_cast<Tile*>(mapIter.next());
	}
	return entity;
}