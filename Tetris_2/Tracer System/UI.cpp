#include "stdafx.h"
#include "UI.h"

void UI::Draw(sf::RenderWindow& renderWindow, Grid& _grid)
{
	//draw score
	int score = _grid.ReturnScore();
	char scoretext[10];
	itoa(score, scoretext, 10);
	sf::Text TextSCORE(scoretext, font, 16);
	TextSCORE.SetPosition(355, 270);
	renderWindow.Draw(TextSCORE, sf::RenderStates::Default);

	//draw level
	int level = _grid.ReturnLevel();
	char leveltext[10];
	itoa(score, leveltext, 10);
	sf::Text TextLVL(leveltext, font, 48);
	TextLVL.SetPosition(400, 118);
	renderWindow.Draw(TextLVL, sf::RenderStates::Default);

	//draw background
	renderWindow.Draw(s_background);
}

void UI::Load()
{
	t_background.LoadFromFile("background_tetris.png");
	s_background.SetTexture(t_background);

	s_background.SetPosition(0,0);

	font.LoadFromFile("mizufalp.ttf");
}