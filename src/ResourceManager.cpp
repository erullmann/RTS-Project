#include "ResourceManager.h"

void ResourceManager::load()
{
	//load spritesheets
	mapTextureSheet.loadFromFile("tilesheet.png");
	unitTextureSheet.loadFromFile("deer.png");
}

ResourceManager::~ResourceManager(){
	//unload spritesheets
	mapTextureSheet.~Image();
	unitTextureSheet.~Image();
}

sf::Texture *ResourceManager::returnElementTexture(ENTITYTYPE rEntity){
	sf::Texture *texture = new sf::Texture;
	switch (rEntity) {
		case TILE_GRASS:
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 64, 128, 64));
			break;
		case TILE_WOOD:
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 0, 128, 64));
			break;
		case UNIT_DEER:
			texture->loadFromImage(unitTextureSheet, sf::Rect<int>(0, 0, 128, 64));
			break;
		default: //ocean texture
			texture->loadFromImage(mapTextureSheet, sf::Rect<int>(0, 64, 128, 64));
			break;
	}

	return texture;
}