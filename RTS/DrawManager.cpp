#include "DrawManager.h"

void DrawManager::start(LevelManager& levelManager)
{
	//load SpriteSheets
	mapTextureSheet.loadFromFile("tilesheet_good_65.png");
	generateTiles(levelManager, mapTextureSheet);
}

void DrawManager::drawGame(sf::RenderWindow& renderWindow, LevelManager& levelManager)
{
	for (std::vector<TileEntity*>::iterator iter = m_TileList.begin(); iter != m_TileList.end(); iter++)
	{
		(*iter)->draw(renderWindow);
	}
	//do entities
	levelManager.drawAllEntitys(renderWindow);
}

void DrawManager::drawUI(sf::RenderWindow& renderWindow, LevelManager& levelManager)
{
	//nothing yet
}

void DrawManager::end()
{
	//Anything else?
	deleteTiles();
}

void DrawManager::generateTiles(LevelManager& levelManager, sf::Texture& mapTextureSheet)
{
	int** map;
	map = levelManager.getMap();

	sf::Vector2i levelSize;
	levelSize = levelManager.returnLevelSize();
	for (int i = 0; i<levelSize.x; i++)
	{
		for (int j = 0; j<levelSize.y; j++)
		{
			TileEntity* temp = new TileEntity;
			m_TileList.push_back(temp);
			(*(m_TileList.end()-1))->start(mapTextureSheet, map[i][j], 0, i, j);//Will need to replace with more complex tilesprite selection code
		}
	}
}

void DrawManager::deleteTiles()
{
	for (std::vector<TileEntity*>::size_type sizeType =0; sizeType < m_TileList.size(); sizeType++)
	{
		m_TileList.erase(m_TileList.begin() + sizeType);
	}
}
