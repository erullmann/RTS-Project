#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Time.h"
#include "Particle.h"
#include "Tracker.h"

class Game
{
public:
	static void Start();
	

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState { Uninitalized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	
	static Time _time;
	static sf::Vector2f _initInput;

	static Tracker _tracker;
	static int _massSetting;
	static int halfScreenX;
	static int halfScreenY;
	
};