#pragma once
#include "stdafx.h"
#include "Block.h"

////////////////////
//Public Functions//
////////////////////

void Block::SetPos(int INx, int INy)
{
	x = INx;
	y = INy;
}

void Block::Move(int INx, int INy)
{
	x += INx;
	y += INy;

	markMove = 0;
}

sf::Vector2f Block::ReturnPos()
{
	sf::Vector2f temp;
	temp.x = x;
	temp.y = y;
	return temp;
}

void Block::SetColor(sf::Color INcolor)
{
	color = INcolor;
}

sf::Color Block::ReturnColor()
{
	return color;
}

void Block::SetMode(int INmode)
{
	mode = INmode;
}

int Block::ReturnMode()
{
	return mode;
}

void Block::Delete()//sets mode to 3, moves to -1,-1
{
	SetMode(3);
	SetPos(-1, -1);
}

void Block::MarkMove()
{
	markMove++;
}

int Block::ReturnMarkMove()
{
	return markMove;
}