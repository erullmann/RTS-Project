#include <SFML/Graphics.hpp>
#include "LevelManager.h"
#include "DrawManager.h"

int main()
{


	sf::RenderWindow renderWindow(sf::VideoMode(1366, 768), "A Race For Oil", sf::Style::Fullscreen);
	renderWindow.setVerticalSyncEnabled(true);
	DrawManager drawManager;
	LevelManager levelManager;

	levelManager.load("blank");
	drawManager.start(levelManager);

	sf::View view(sf::Rect<float>(-683, -384, 1366, 768));
	renderWindow.setView(view);

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
				view.move(-5.0, 0.0);
				renderWindow.setView(view);
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Right) 
			{
				view.move(5.0, 0.0);
				renderWindow.setView(view);
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Up) 
			{
				view.move(0.0, -5.0);
				renderWindow.setView(view);
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Down) 
			{
				view.move(0.0, 5.0);
				renderWindow.setView(view);
			}
        }

		renderWindow.clear();
		//levelManager.updateLevel();
		drawManager.drawGame(renderWindow, levelManager);
		drawManager.drawUI(renderWindow, levelManager);
		renderWindow.display();
    }

    return 0;
}