#include "ResourceManager.h"

void ResourceManager::load()
{
	//load spritesheets
	mapTextureSheet.loadFromFile("tilesheet_good_65.png");
	unitTextureSheet.loadFromFile("tank_body.png");
}

ResourceManager::~ResourceManager(){
	//unload spritesheets
	mapTextureSheet.~Image();
	unitTextureSheet.~Image();
}

sf::Texture *ResourceManager::returnElementTexture(ENTITYTYPE rEntity){
	sf::Texture texture;
	switch (rEntity) {
		case TILE_OCEAN:
			texture.loadFromImage(unitTextureSheet, sf::Rect<int>(100, 0, 100, 65));
			break;
		case TILE_GRASS:
			texture.loadFromImage(unitTextureSheet, sf::Rect<int>(0, 0, 100, 65));
			break;
		case UNIT_TANK:
			texture.loadFromImage(unitTextureSheet, sf::Rect<int>(0, 0, 384, 48));
			break;
		default: //ocean texture
			texture.loadFromImage(unitTextureSheet, sf::Rect<int>(0, 0, 384, 48));
			break;
	}

	return &texture;
}