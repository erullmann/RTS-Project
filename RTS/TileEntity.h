///////////////////
//TileEntity class: holds and manages a single tilesprite
///////////////////
#pragma once
#include "SFML\Graphics.hpp"


class TileEntity 
{
public: 

	void start(sf::Texture& spriteSheet, int xSpriteCord, int ySpriteCord, int xPos, int yPos);

	void draw(sf::RenderWindow &renderWindow);

private:

	static const int spriteWidth = 100;

	static const int spriteHeight = 64;

	sf::Sprite sprite;

	int XPos, YPos;

};