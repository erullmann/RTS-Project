#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "LevelManager.h"
#include "DrawManager.h"

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
	std::srand(time(NULL));
	sf::Clock clock;
	sf::Vector2f mapOffset(0, 0);

	sf::RenderWindow renderWindow(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "A Race For Oil", sf::Style::Default);
	renderWindow.setVerticalSyncEnabled(true);
	DrawManager drawManager;
	LevelManager levelManager;
	
	levelManager.load("blank");//we can put real maps in later
	
	drawManager.start(levelManager);
	
	renderWindow.setView(view);

	clock.restart();

    while (renderWindow.isOpen())
    {
        sf::Event currentEvent;
        while (renderWindow.pollEvent(currentEvent))
        {
            if (currentEvent.type == sf::Event::Closed)
                renderWindow.close();

			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape)
			{
				renderWindow.close();
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Left) 
			{
				view.move(-cameraMovementSpeed, 0.0);
				renderWindow.setView(view);
				mapOffset.x -= cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Right) 
			{
				view.move(cameraMovementSpeed, 0.0);
				renderWindow.setView(view);
				mapOffset.x += cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Up) 
			{
				view.move(0.0, -cameraMovementSpeed);
				renderWindow.setView(view);
				mapOffset.y -= cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Down) 
			{
				view.move(0.0, cameraMovementSpeed);
				renderWindow.setView(view);
				mapOffset.y += cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::T) 
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				levelManager.addEntity(screenToMapTransform(mousePos, renderWindow, mapOffset), 0, 0);
			}
			if (currentEvent.type == sf::Event::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				//levelManager.select(screenToMapTransform(mousePos, renderWindow, mapOffset));
			}
        }

		renderWindow.clear(sf::Color(255, 255, 255, 255));
		
		levelManager.updateLevel(clock.restart());
		
		drawManager.drawGame(renderWindow, levelManager);
		drawManager.drawUI(renderWindow, levelManager);
		renderWindow.display();
    }

    return 0;
}