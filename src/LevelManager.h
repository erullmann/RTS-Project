///////////////////////////////////////////////
//Level Manager 
//Holds and manages the level
///////////////////////////////////////////////
#pragma once

#include <iostream>
#include "BaseEntity.h"
#include "EntityType.h"
#include "EntityList.h"
#include "Tile.h"
#include "Deer.h"

class LevelManager
{
public:
	
	LevelManager(sf::RenderWindow &renderWindow, ResourceManager &resourceManager);

	//Core level managment
	void load(std::string levelname, sf::RenderWindow& renderWindow);	//loads level

	void unload();						//unloads level for main menu/quitting, requests: do you want to save?; erases Entitys, erases blocks
	
	void save(std::string filename); //saves level

	void generate(int seed);		//generates level
	
	//update calls
	void updateLevel(sf::Time frameTime);//updates level, itterates through Entitylist; deletes flagged Entitys RE:deleteEntity()

	//Level management calls
	void addEntity(sf::Vector2f position, ENTITYTYPE type);	//adds Entitys, usually on level load or in-game creation

	void deleteEntity(BaseEntity *entity); //deletes Entitys with delete flag

	void deleteAllEntitys();

	void drawAllEntitys();

	void pauseGame();

	EntityList *getMapList();

	EntityList *getUnitList();

	sf::Vector2i returnLevelSize();

private:
	
	EntityList *_mapList; //pointer to level collision array

	EntityList *_unitList;

	sf::Vector2i _levelSize; //height and width of level in tiles

	ResourceManager *_resourceManager;

	sf::RenderWindow *_renderWindow;

	bool isPaused; //pauses game 

};