#pragma once
#include "Game.h"

Game::GAMESTATE Game::_gameState = UNINITIALIZED;

void Game::StartGame(){
	if (_gameState != UNINITIALIZED)
		return;

	//load/set up reasources
	_resourceManager.load();
	_renderWindow.create(sf::VideoMode(SCREEN_X, SCREEN_Y, 32), "Explore");
	
	_gameState = MAINMENU;

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
	_resourceManager.~ResourceManager();
	_renderWindow.close();
}