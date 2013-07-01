
#include "LevelManager.h"

LevelManager::LevelManager(sf::RenderWindow &renderWindow, ResourceManager &resourceManager){
	_renderWindow = &renderWindow;
	_resourceManager = &resourceManager;
	_mapList = new EntityList;
	_unitList = new EntityList;
}

void LevelManager::load(std::string levelname, sf::RenderWindow& renderWindow){
	//not used for now
	isPaused = false;
	_levelSize.x = 40;
	_levelSize.y = 40;

	
	///////////
	//Entity management
	///////////

}

void LevelManager::unload(){
	deleteAllEntitys();
}

void LevelManager::save(std::string filename)
{
	//saving XML code
}

void LevelManager::generate(int seed){
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			float rand = std::rand() % 10;
			ENTITYTYPE type;
			if (rand < 3)
				type = TILE_WOOD;
			else
				type = TILE_GRASS;
			Tile *temp = new Tile(sf::Vector2f(i, j), sf::Vector2i(128, 64), *_renderWindow, *_resourceManager, type, 0);
			_mapList->pushBack(temp);
		}
	}

	EntityListIterator mapIter(_mapList);
	Tile *tile = static_cast<Tile*>(mapIter.curr());
	while(tile != NULL){
		tile->_nodeComponent->findNeighbors(*_mapList, *tile, sf::Vector2i(10, 10));
		tile = static_cast<Tile*>(mapIter.next());
	}

	Deer *temp = new Deer(sf::Vector2f(5, 0), sf::Vector2f(0,0), _mapList, _unitList, NULL, *_resourceManager, *_renderWindow);
	_unitList->pushBack(temp);
	temp->setDest(sf::Vector2f(1, 7));
}

void LevelManager::updateLevel(sf::Time frame_time){
	EntityListIterator unitIter(_unitList);
	BaseEntity *currEntity = unitIter.curr();

	while (currEntity != NULL)
	{
		currEntity->update(frame_time);
		currEntity = unitIter.next();
	}
}

void LevelManager::addEntity(sf::Vector2f pos, ENTITYTYPE type){
	BaseEntity* pEntity;
	//change to switch statment
	if (type == TILE_OCEAN){
		pEntity = new Tile(sf::Vector2f(pos.x, pos.y), sf::Vector2i(64, 32), *_renderWindow, *_resourceManager, type, 0);
		_mapList->pushBack(pEntity);
	}else{
		pEntity = new Tile(sf::Vector2f(pos.x, pos.y), sf::Vector2i(64, 32), *_renderWindow, *_resourceManager, type, 0);//temp
		_mapList->pushBack(pEntity);
	}	
}


void LevelManager::deleteEntity(BaseEntity *entity){
	//add member() and delete() functions to EntityList
}

void LevelManager::deleteAllEntitys(){
	_mapList->deleteList();
	_unitList->deleteList();
}

void LevelManager::drawAllEntitys(){
	EntityListIterator mapIter(_mapList);
	EntityListIterator unitIter(_unitList);

	BaseEntity *currEntity = mapIter.curr();
	while (currEntity != NULL)
	{
		currEntity->draw();
		currEntity = mapIter.next();
	}

	currEntity = unitIter.curr();
	while (currEntity != NULL)
	{
		currEntity->draw();
		currEntity = unitIter.next();
	}
	
}

void LevelManager::pauseGame(){
	isPaused = !isPaused; //toggles pausegame
}

EntityList *LevelManager::getMapList(){
	return _mapList;
}

EntityList *LevelManager::getUnitList(){
	return _unitList;
}


sf::Vector2i LevelManager::returnLevelSize(){
	return _levelSize;
}