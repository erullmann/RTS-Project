#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include "Grid.h"

class UI
{
public:
	void Draw(sf::RenderWindow& renderWindow, Grid& _grid);
	
	void Load();

private:
	sf::Texture t_background;
	sf::Sprite s_background;
	sf::Font font;
};