/* DrawComponent.h
   Provides drawing functionality to all those who want it
*/
#pragma once
#include "SFML\Graphics.hpp"
#include "ResourceManager.h"
#include "Tile.h"

class DrawComponent {
public:

	DrawComponent(ResourceManager *resourceManager, sf::Vector2i spriteSize, int numberOfFrames);

	void drawInGame(sf::RenderWindow &renderWindow, Tile *self);

	void drawOnWindow(sf::RenderWindow &renderWindow);


};