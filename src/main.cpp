#include "SFML/Graphics.hpp"
#include "Game.h"

#define SCREENWIDTH		800
#define SCREENHEIGHT	600

int cameraMovementSpeed = 5;
sf::View view(sf::Vector2f(0, 0), sf::Vector2f(SCREENWIDTH, SCREENHEIGHT));


//Transforms mouseclicks to Map positions
sf::Vector2f screenToMapTransform(sf::Vector2i click, sf::RenderWindow& renderWindow, sf::Vector2f mapOffset)
{
	int spriteWidth = 100;
	int spriteHeight = 64;
	
	//adapt click to top of map
	sf::Vector2f screenClick;
	
	screenClick.x = click.x - renderWindow.getPosition().x - (SCREENWIDTH/2) + mapOffset.x;
	screenClick.y = click.y - renderWindow.getPosition().y - (SCREENHEIGHT/2) + mapOffset.y;
	
	//screenClick.x = renderWindow.convertCoords(click).x;
	//screenClick.y = renderWindow.convertCoords(click).y;
	
	//transform screen position to map position
	float XPos = ((screenClick.x/(spriteWidth/2)) + (screenClick.y/(spriteHeight/2)))/2;
	float YPos = ((screenClick.y/(spriteHeight/2)) - (screenClick.x/(spriteWidth/2)))/2;
	sf::Vector2f position(XPos, YPos);
	return position;
}

int main()
{
	Game _game;

	_game.StartGame();

    return 0;
}