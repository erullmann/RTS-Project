
#pragma once
#include "LevelManager.h"

int **LevelManager::m_Map = NULL;

int LevelManager::load(std::string levelname)
{
	isPaused = false;
	levelSize.x = 40;
	levelSize.y = 40;

	//temperary level, replace with XML reader
	//int level[40][40] = {
	//	1, 1, 1, 0, 0,
	//	1, 1, 1, 1, 0,
	//	0, 0, 1, 1, 1,
	//	0, 0, 0, 1, 1,
	//	1, 1, 1, 1, 1,
	//};
	//temp amount of Entitys, consider adding 10 or so to the loaded amount to account for arrows and the like

	int amountOfEntitys = 20;

	/////////////
	//loading level pointer with random tiles
	/////////////

	std::srand(time(NULL));

	//create rows
	m_Map = new int*[levelSize.x];
	//create columns
	for (int i = 0; i<levelSize.x; i++)
	{
		m_Map[i] = new int [levelSize.x];
	}
	//fill level
	for (int i=0; i<levelSize.x; i++)
	{
		for (int j=0; j<levelSize.y; j++)
		{
			int random = std::rand()%2;
			m_Map[i][j] = random;
		}
	}
	
	///////////
	//Entity management
	///////////

	m_EntityList.reserve(amountOfEntitys);

	//temp adding Entitys
	

	return 1;
}

void LevelManager::unload()
{
	for (int i=0; i<levelSize.x; i++)
	{
		for (int j=0; j<levelSize.y; j++)
		{
			m_Map[i][j] = 0;
		}
	}

	deleteAllEntitys();
}

int LevelManager::save()
{
	//saving XML code
	return 1;
}

void LevelManager::updateLevel(int& levelPtr, std::vector<BaseEntity*>& EntityListPtr)
{
	for (m_EntityListIter = m_EntityList.begin(); m_EntityListIter != m_EntityList.end(); m_EntityListIter++)
	{
		(*m_EntityListIter)->update(levelPtr, EntityListPtr);
	}
}

void LevelManager::addEntity(float x, float y, int typeID)
{
	sf::Vector2f position;
	position.x = x;
	position.y = y;
	switch (typeID) 
	{
	case 0:
		;//create unit, building, etc.
	}
	
}

void LevelManager::deleteEntity()
{
	for (m_EntityListIter = m_EntityList.begin(); m_EntityListIter != m_EntityList.end(); m_EntityListIter++)
	{
		if ((*m_EntityListIter)->returnDeleteFlag() == true)
			m_EntityList.erase(m_EntityListIter);
	}
}

void LevelManager::deleteAllEntitys()
{
	for (m_EntityListIter = m_EntityList.begin(); m_EntityListIter != m_EntityList.end(); m_EntityListIter++)
	{
		m_EntityList.erase(m_EntityListIter);
	}
}

void LevelManager::pauseGame()
{
	isPaused != isPaused; //toggles pausegame
}

int **LevelManager::returnMap()
{
	return m_Map;
}

std::vector<BaseEntity*> LevelManager::returnEntityList()
{
	return m_EntityList; //returns list of entities for drawing and such
}

sf::Vector2i LevelManager::returnLevelSize()
{
	return levelSize;
}