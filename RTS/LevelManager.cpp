
#include "LevelManager.h"

int **LevelManager::m_Map = NULL;

int LevelManager::load(std::string levelname)
{
	isPaused = false;
	levelSize.x = 40;
	levelSize.y = 40;

	/////////////
	//loading level pointer with random tiles
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

void LevelManager::updateLevel(sf::Time frame_time)
{
	for (std::vector<BaseEntity*>::iterator m_EntityListIter = m_EntityList.begin(); m_EntityListIter != m_EntityList.end(); m_EntityListIter++)
	{
		(*m_EntityListIter)->update(frame_time, this->returnEntityList(), this->getMap());
	}
}

int LevelManager::addEntity(sf::Vector2f position, int typeID, int team)
{
	BaseEntity* pEntity;
	//change to switch statment
	if (typeID == 0)
		pEntity = new Tank;
	else
		pEntity = new Tank;//temp

	//find availible IDs
	int id;

	if (m_FreeEntityList.empty())
	{
		id = m_EntityList.size();
		m_EntityList.push_back(pEntity);
	}
	else
	{
		id = m_FreeEntityList.back();
		m_FreeEntityList.pop_back();
		m_EntityList[id] = pEntity;
	}

	m_EntityList[id]->start(position, team);

	return typeID;
}


void LevelManager::deleteEntity()
{
	std::vector<BaseEntity*>::iterator m_EntityListIter = m_EntityList.begin();
	for (unsigned int i = 0; i < m_EntityList.size(); i++)
	{
		if (m_EntityListIter[i]->returnDeleteFlag() == true)
		{
			(*m_EntityListIter)->destroy();
			m_FreeEntityList.push_back(i);
		}
		i++;
	}
}

void LevelManager::deleteAllEntitys()
{
	std::vector<BaseEntity*>::iterator m_EntityListIter = m_EntityList.begin();
	while (m_EntityListIter != m_EntityList.end())
	{
		(*m_EntityListIter)->destroy();
		m_EntityListIter = m_EntityList.erase(m_EntityListIter);
	}
}

void LevelManager::drawAllEntitys(sf::RenderWindow& renderWindow)
{
	std::vector<BaseEntity*>::iterator m_EntityListIter = m_EntityList.begin();
	while (m_EntityListIter != m_EntityList.end())
	{
		(*m_EntityListIter)->draw(renderWindow);
		m_EntityListIter++;
	}
}

void LevelManager::pauseGame()
{
	isPaused != isPaused; //toggles pausegame
}

int **LevelManager::getMap()
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