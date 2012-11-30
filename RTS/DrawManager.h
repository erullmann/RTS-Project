////////////////////
//DrawManager: draws and displays the map and ingame objects and UI
///////////////////
#include "SFML\Graphics.hpp"
#include "TileEntity.h"
#include "LevelManager.h"

class DrawManager 
{
public:

	void start(LevelManager& levelManager);

	void drawGame(sf::RenderWindow& renderWindow, LevelManager& levelManager);

	void drawUI(sf::RenderWindow& renderWindow, LevelManager& levelManager);

	void end();

private:

	void generateTiles(LevelManager& levelManager, sf::Texture& mapTextureSheet);

	void deleteTiles();

	sf::Texture mapTextureSheet; //main texture for map tiles

	std::vector<TileEntity*> m_TileList;

};