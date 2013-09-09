/* PathfindingService.h
 Header for the pathfinding service class
 -provides point A->B pathfinding 
 -different movement classes can use it
 -used as a singleton
 */

#include "EntityList.h"
#include "Tile.h"
#include "Types.h"

class PathfindingService {
public:

	//intialize pathfinding service and get map reference
	PathfindingService(EntityList *map);

	//findPath(start, dest)
	//returns vector list of points to destination, reciever must properly dispose of list to prevent memory leaks
	//list is new each time and organized as a stack with endLocation at the top of the stack and startLocation at the bottom
	//moementType is how the creatue can move (flys, walks, swims, etc), allows for correct pathing and prevents falling off cliffs
	std::vector<sf::Vector2i>* findPath(sf::Vector2i startLocation, sf::Vector2i endLocation, MOVEMENTTYPE movementType);

private:

	Tile *returnLowestFScore(EntityList *list);

	Tile *returnTileEntity(sf::Vector2i location);

	EntityList *_map;

};