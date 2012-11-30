///////////////////////////////////////////////
//Level Manager 
//Holds and manages the level
///////////////////////////////////////////////
#pragma once

#include <iostream>
#include "BaseEntity.h"
#include "Tank.h"

class LevelManager
{
public:
	
	//Core level managment
	int load(std::string levelname);	//loads level

	void unload();						//unloads level for main menu/quitting, requests: do you want to save?; erases Entitys, erases blocks
	
	int save();							//saves level

	int generate();						//generates level
	
	//update calls
	void updateLevel(sf::Time frameTime);//updates level, itterates through Entitylist; deletes flagged Entitys RE:deleteEntity()

	//Level management calls
	int addEntity(sf::Vector2f position, int typeID, int team);					//adds Entitys, usually on level load or in-game creation

	void deleteEntity(); //deletes Entitys with delete flag

	void deleteAllEntitys();

	void drawAllEntitys(sf::RenderWindow& renderWindow);

	void pauseGame();

	int **getMap();

	std::vector<BaseEntity*> returnEntityList();

	sf::Vector2i returnLevelSize();

private:
	
	static int **m_Map; //pointer to level collision array

	sf::Vector2i levelSize; //height and width of level in tiles

	///INTERACTIVE Entitys///
	std::vector<BaseEntity*> m_EntityList; //full list of ingame Entitys, ex: units, trees, buildings, ecetera

	std::vector<int> m_FreeEntityList;

	std::vector<BaseEntity*> m_EntityTeamList[9]; //conncerent entity lists for each team; 0 is world, 1-8 are players 
	                                              //consider moving to PlayerEntity

	bool isPaused; //pauses game 

};