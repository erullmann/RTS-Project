#include "stdafx.h"
#include "Game.h"
#include <iostream>

void Game::Start()
{
	if (_gameState != Uninitalized)
		return;
	sf::View view;
	view.SetSize((800), (600));
	view.SetCenter(400, 300);
	_mainWindow.Create(sf::VideoMode((800), (600), 32), "Particles", sf::Style::Default);
	_mainWindow.SetView(view);
	_initInput.x = 0;
	_initInput.y = 0;

	_gameState = Game::Playing;
	_tracker.Initialise(500);
	_massSetting = 10;

	while (!IsExiting())
		GameLoop();

	_mainWindow.Close();
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
	_mainWindow.PollEvent(currentEvent);
		switch (_gameState)
		{
			case Game::Playing:
			{
			
			_mainWindow.Clear(sf::Color(0, 0, 0));
			float timeFactor = _time.GetTimeSinceLastFrame();

			_tracker.IterateParticles(timeFactor, _mainWindow);

			_mainWindow.Display();
			//std::cout<< _time.GetTimeSinceLastFrame() << "\n";
			_time.ResetFrameTime();
			if (currentEvent.Type == sf::Event::Closed)
				_gameState = Game::Exiting;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Escape))
				_gameState = Game::Exiting;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Num1))
				_massSetting = 10;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Num2))
				_massSetting = 100;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Num3))
				_massSetting = 1000;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Num4))
				_massSetting = -100000;
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Num5))
				_massSetting = 100000;
			if ((currentEvent.Type == sf::Event::MouseButtonPressed) && (currentEvent.MouseButton.Button == sf::Mouse::Left))
			{
				const sf::Mouse mouse;

				_initInput.x = (mouse.GetPosition(_mainWindow).x);
				_initInput.y = (mouse.GetPosition(_mainWindow).y);
				std::cout<<_initInput.x<<", "<<_initInput.y<<"\n";
			}
			if ((currentEvent.Type == sf::Event::MouseButtonReleased) && (currentEvent.MouseButton.Button == sf::Mouse::Left))
			{
				const sf::Mouse mouse;
				sf::Vector2i _input;
				_input = (mouse.GetPosition(_mainWindow));

				sf::Vector2f _velocity;
				_velocity.x = (_initInput.x - _input.x);
				_velocity.y = (_initInput.y - _input.y);

				std::cout<<_input.x<<", "<<_input.y<<"\n";
				std::cout<<_velocity.x<<", "<<_velocity.y<<"\n";

				_tracker.AddParticle(_initInput, _velocity, _massSetting);
			}
			if ((currentEvent.Type == sf::Event::KeyPressed) && (currentEvent.Key.Code == sf::Keyboard::Space))
				_tracker.FreeAll();
			if ((currentEvent.Type == sf::Event::MouseButtonPressed) && (currentEvent.MouseButton.Button == sf::Mouse::Right))
			{
				const sf::Mouse mouse;
				sf::Vector2f _input;
				_input.x = (mouse.GetPosition(_mainWindow).x);
				_input.y = (mouse.GetPosition(_mainWindow).y);
				_tracker.GenerateProtoDisk(_massSetting, _input);
			}
			
			break;
		}
	}
}

Game::GameState Game::_gameState = Uninitalized;
sf::RenderWindow Game::_mainWindow;
Time Game::_time;
sf::Vector2f Game::_initInput;
Tracker Game::_tracker;
int Game::_massSetting;
int Game::halfScreenX = 512;
int Game::halfScreenY = 400;