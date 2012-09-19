#pragma once
#include "stdafx.h"
#include "SFML\Graphics.hpp"

//each block is in one of four
//ACTIVE: blocks are moved on tick sequences and when movement bottons are pressed  [0]
//STILL: blocks don't respond to ticks  [1]
//ELIMINATE: elimination mode, blocks flash  [2]
//INACTIVE: Not doing anything [3]
class Block
{
private:
	int x;
	int y;

	sf::Color color;

	int mode;

	int markMove;

public:
	void SetPos(int x, int y);

	void Move(int x, int y);

	void MarkMove();

	int ReturnMarkMove();

	sf::Vector2f ReturnPos();

	void SetColor(sf::Color color);

	sf::Color ReturnColor();

	void SetMode(int mode);

	int ReturnMode();

	void Delete();//sets mode to 3, moves to -1,-1
};