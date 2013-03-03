/* Pathfinding.cpp
   
   Functions providing A* pathfinding. 
   Most require some sort of moement-cost map (to path routes).
*/

#include "PathFinding.h"

int **generateCostMap(int **map, sf::Vector2i mapSize, UNITTYPE type){
	for (int i = 0; i < mapSize.x; i++){
		for (int j = 0; j < mapSize.y; j++){
			if (type = AIR){
				map[i][j] = 0; //air units have no movement cost
			}
			else if (map[i][j] == type){
				map[i][j] = 0; //cost is zero for land types of the same type as the unit
			}
			else{
				map[i][j] = -1; //inassesable
			}
		}
	}
	return map;
}

sf::Vector2f *generateRoute(int **costMap, sf::Vector2f unitLoc, sf::Vector2f unitDest){
	return &sf::Vector2f(0, 0);
}