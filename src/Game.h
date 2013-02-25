/* file: Game.h
	This file provides the state switching and gameloop processes for the game
*/
#pragma once
#include "LevelManager.h"
#include "ResourceManager.h"
#include "SFML\Graphics.hpp"

#define SCREEN_X	1024
#define SCREEN_Y	768

class Game{
public:
	//loads objects, images, and other reasorces
	//creates main window
	//displays a splash screen as soon as possible
	static void StartGame();
	
private:
	//Returns true if the game is exiting
	static bool IsExiting();

	//Main game loop for the game (as the name suggests)
	//updates game and draws it
	//accepts input and passes it to the approptiote actors
	static void GameLoop();

	//Main menu loop
	//displays and accepts inputs for main menu
	//will allow option changing, game loading etc.
	//for now just play and exit
	static void MainMenu();

	//In game menu loop
	//Game menu displayed while paused
	//for now just resume and exit
	static void PauseMenu();

	enum GAMESTATE { UNINITIALIZED, MAINMENU, PLAYING, PAUSED, EXITING };

	//state we're in right now
	static GAMESTATE _gameState;

	static ResourceManager _resourceManager;

	static sf::RenderWindow _renderWindow;

	static LevelManager _levelManager;
};