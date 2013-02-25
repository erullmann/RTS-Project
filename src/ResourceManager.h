/* ResoucesManager.h
   Loads and manages resouces for the game, allowing tiles and units to access images they need
  */
#pragma once
#include "SFML\Graphics.hpp"
#include "EntityType.h" 


//the various entities who have display elements or who might request resources

class ResourceManager {
public:
	//Constuctor, loads images
	ResourceManager();
	
	//unloads images
	~ResourceManager();

	//When given the entity type, this returns the proper texture information 
	sf::Texture *returnElementTexture(ENTITYTYPE requestingEntity);

private:

	sf::Image mapTextureSheet; //main image for map tiles

	sf::Image unitTextureSheet; //main image for units

};