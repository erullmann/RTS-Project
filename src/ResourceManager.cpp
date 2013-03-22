#include "ResourceManager.h"

void ResourceManager::load()
{
	//load spritesheets
	mapTextureSheet.loadFromFile("grass_tilesheet.png");
	unitTextureSheet.loadFromFile("tilesheet.png");
}

ResourceManager::~ResourceManager(){
	//unload spritesheets
	mapTextureSheet.~Image();
	unitTextureSheet.~Image();
}

sf::Texture *ResourceManager::returnElementTexture(ENTITYTYPE rEntity){
	sf::Texture *texture = new sf::Texture;
	switch (rEntity) {
		case TILE_OCEAN:
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 0, 128, 64));
			break;
		case TILE_GRASS:
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 0, 128, 64));
			break;
		case UNIT_DEER:
			texture->loadFromImage(unitTextureSheet, sf::Rect<int>(0, 0, 384, 48));
			break;
		default: //ocean texture
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 0, 128, 64));
			break;
	}

	return texture;
}