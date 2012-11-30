
#include "TileEntity.h"

void TileEntity::start(sf::Texture& spriteSheet, int xSpriteCord, int ySpriteCord, int xPos, int yPos)
{
	//image
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::Rect<int>(xSpriteCord*spriteWidth, ySpriteCord*spriteHeight, spriteWidth, spriteHeight));

	XPos = (xPos*(spriteWidth/2)) - (yPos*(spriteWidth/2)) - (spriteWidth/2);
	YPos = (yPos*(spriteHeight - 14)/2) + (xPos*(spriteHeight - 14)/2);
	sprite.setPosition(XPos, YPos);
}

void TileEntity::draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
}