#define SCREENWIDTH		520
#define SCREENHEIGHT	618
#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "Grid.h"
#include "UI.h"

class Game
{
public:

	static void Start();

private:

	static bool IsExiting();

	static void GameLoop();

	enum GameState {Uninitalized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _renderWindow;
	static Grid _grid;
	static UI _ui;
};