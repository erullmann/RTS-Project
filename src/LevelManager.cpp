
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
			ENTITYTYPE type = TILE_GRASS;
			Tile *temp = new Tile(sf::Vector2f(i, j), sf::Vector2i(128, 64), *_renderWindow, *_resourceManager, type, 0);
			_mapList->pushBack(temp);
		}
	}
}

void LevelManager::updateLevel(sf::Time frame_time){
	_unitList->resetIterator(); //just to be safe

	BaseEntity *currEntity = _unitList->iterateEntites();
	while (currEntity != NULL)
	{
		currEntity->update(frame_time);
		currEntity = _unitList->iterateEntites();
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
	_mapList->resetIterator();
	_unitList->resetIterator();

	BaseEntity *currEntity = _mapList->iterateEntites();
	while (currEntity != NULL)
	{
		currEntity->draw();
		currEntity = _mapList->iterateEntites();
	}

	currEntity = _unitList->iterateEntites();
	while (currEntity != NULL)
	{
		currEntity->draw();
		currEntity = _mapList->iterateEntites();
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