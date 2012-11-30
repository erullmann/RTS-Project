#include "stdafx.h"
#include "Game.h"

//varibles//
Game::GameState Game::_gameState = Uninitalized;
sf::RenderWindow Game::_renderWindow;
Grid Game::_grid;
UI Game::_ui;
///////////

void Game::Start()
{
	if (_gameState != Uninitalized)
		return;
	
	_renderWindow.Create(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT, 32), "The Sky Is Falling!", sf::Style::Default);

	_gameState = Game::Playing;
	_grid.Start(0, 0);
	_ui.Load();

	while (!IsExiting())
		GameLoop();

	_renderWindow.Close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else 
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_renderWindow.PollEvent(currentEvent);
	switch (_gameState)
	{
	case Game::Playing:
		{
			_renderWindow.Clear(sf::Color(0, 0, 0, 255));

			_grid.Tick();
			_grid.Draw(_renderWindow);
			_ui.Draw(_renderWindow, _grid);

			_renderWindow.Display();

			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Left))
			{
				_grid.MoveLeft();
			}
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Right))
			{
				_grid.MoveRight();
			}
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Down))
			{
				_grid.MoveDown();
			}
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Up))
			{
				_grid.MoveRotate();
			}

			if (currentEvent.Type == sf::Event::Closed)
				_gameState = Game::Exiting;
		}
	}
}