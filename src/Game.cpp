#pragma once
#include "Game.h"

Game::GAMESTATE Game::_gameState = UNINITIALIZED;
ResourceManager *Game::_resourceManager;
sf::RenderWindow *Game::_renderWindow;
LevelManager *Game::_levelManager;

void Game::StartGame(){
	if (_gameState != UNINITIALIZED)
		return;

	//load/set up reasources
	_resourceManager = new ResourceManager;
	_renderWindow = new sf::RenderWindow;
	_resourceManager->load();
	_renderWindow->create(sf::VideoMode(SCREEN_X, SCREEN_Y, 32), "Explore");
	
	_gameState = PLAYING;//PLAYING for now, change to MAINMENU

	while (!IsExiting()){
		switch (_gameState){
		case UNINITIALIZED:
			return; //we shouldn't be here
			break;
		case MAINMENU:
			MainMenu();
			break;
		case PLAYING:
			GameLoop();
			break;
		case PAUSED:
			PauseMenu();
			break;
		}
	}

	//unload memory
	_resourceManager->~ResourceManager();
	_renderWindow->close();
}

bool Game::IsExiting(){
	if (_gameState == EXITING)
		return true;
	else 
		return false;
}

void Game::GameLoop(){
	std::srand(time(NULL));
	sf::Clock clock;
	sf::Vector2f mapOffset(0, 0);

	int cameraMovementSpeed = 5;
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(SCREEN_X, SCREEN_Y));
	
	_levelManager = new LevelManager(*_renderWindow, *_resourceManager);
	_levelManager->generate(234);//we can put real maps in later
	
	_renderWindow->setView(view);

	clock.restart();

    while (_renderWindow->isOpen())
    {
        sf::Event currentEvent;
        while (_renderWindow->pollEvent(currentEvent))
        {
            if (currentEvent.type == sf::Event::Closed)
				_gameState = EXITING;

			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Escape)
			{
				_gameState = EXITING;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Left) 
			{
				view.move(-cameraMovementSpeed, 0.0);
				_renderWindow->setView(view);
				mapOffset.x -= cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Right) 
			{
				view.move(cameraMovementSpeed, 0.0);
				_renderWindow->setView(view);
				mapOffset.x += cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Up) 
			{
				view.move(0.0, -cameraMovementSpeed);
				_renderWindow->setView(view);
				mapOffset.y -= cameraMovementSpeed;
			}
			if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Down) 
			{
				view.move(0.0, cameraMovementSpeed);
				_renderWindow->setView(view);
				mapOffset.y += cameraMovementSpeed;
			}
			/*if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::T) 
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				levelManager.addEntity(screenToMapTransform(mousePos, renderWindow, mapOffset), 0, 0);
			}
			if (currentEvent.type == sf::Event::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				//levelManager.select(screenToMapTransform(mousePos, renderWindow, mapOffset));
			}*/
        }

		_renderWindow->clear(sf::Color(255, 255, 255, 255));
		
		_levelManager->updateLevel(clock.restart());
		_levelManager->drawAllEntitys();
		
		_renderWindow->display();
    }
}

void Game::MainMenu(){

}

void Game::PauseMenu(){

}