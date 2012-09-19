#include "stdafx.h"
#include "Grid.h"
#include <iostream>

////////////////////
//Public Functions//
////////////////////

void Grid::Start(int in_level, int in_score)
{
	score = in_score;
	level = in_level;
	img_block.LoadFromFile("block.png");
	spt_block.SetTexture(img_block, false); 
	lastTickTime.Restart();
	lineEliminationMode = false;

	for(int i=0; i<180; i++)
	{
		m_Grid[i].Delete();
	}

	SpawnBlock();
}

void Grid::Draw(sf::RenderWindow& renderWindow)//sorts through all blocks and draws them. UI draws score and such
{
	for(int i=0; i<180; i++)
	{
		if (m_Grid[i].ReturnMode() == 2)
			spt_block.SetColor(sf::Color(255, 255, 255, 255));
		else
			spt_block.SetColor(m_Grid[i].ReturnColor());
		sf::Vector2f temp;
		temp.x = (32 * (m_Grid[i].ReturnPos().x)) + 5;
		temp.y = (32 * (m_Grid[i].ReturnPos().y)) + 5;
		spt_block.SetPosition(temp);
		renderWindow.Draw(spt_block);
	}
}

void Grid::MoveDown() //Moves current block down right away, adds to score, calls: CheckCollisions
{
	sf::Vector2f POS[4];
	POS[0] = m_Grid[ID[0]].ReturnPos();
	POS[1] = m_Grid[ID[1]].ReturnPos();
	POS[2] = m_Grid[ID[2]].ReturnPos();
	POS[3] = m_Grid[ID[3]].ReturnPos();
	
	if (lineEliminationMode == true)
	{
		//do nothing
	}
	else
	{
		m_Grid[ID[0]].Move(0, 1);
		m_Grid[ID[1]].Move(0, 1);
		m_Grid[ID[2]].Move(0, 1);
		m_Grid[ID[3]].Move(0, 1);
	}

	if (CheckCollisions() == true)
	{
		m_Grid[ID[0]].SetPos(POS[0].x, POS[0].y);
		m_Grid[ID[1]].SetPos(POS[1].x, POS[1].y);
		m_Grid[ID[2]].SetPos(POS[2].x, POS[2].y);
		m_Grid[ID[3]].SetPos(POS[3].x, POS[3].y);
	}
}
	
void Grid::MoveRight() //Moves current block right, calls: CheckCollisions
{
	sf::Vector2f POS[4];
	POS[0] = m_Grid[ID[0]].ReturnPos();
	POS[1] = m_Grid[ID[1]].ReturnPos();
	POS[2] = m_Grid[ID[2]].ReturnPos();
	POS[3] = m_Grid[ID[3]].ReturnPos();

	if (lineEliminationMode == true)
	{
		//do nothing
	}
	else
	{
		m_Grid[ID[0]].Move(1, 0);
		m_Grid[ID[1]].Move(1, 0);
		m_Grid[ID[2]].Move(1, 0);
		m_Grid[ID[3]].Move(1, 0);
	}

	if (CheckCollisions() == true)
	{
		m_Grid[ID[0]].SetPos(POS[0].x, POS[0].y);
		m_Grid[ID[1]].SetPos(POS[1].x, POS[1].y);
		m_Grid[ID[2]].SetPos(POS[2].x, POS[2].y);
		m_Grid[ID[3]].SetPos(POS[3].x, POS[3].y);
	}
}

void Grid::MoveLeft() //Moves current block left, calls: CheckCollisions
{
	sf::Vector2f POS[4];
	POS[0] = m_Grid[ID[0]].ReturnPos();
	POS[1] = m_Grid[ID[1]].ReturnPos();
	POS[2] = m_Grid[ID[2]].ReturnPos();
	POS[3] = m_Grid[ID[3]].ReturnPos();

	if (lineEliminationMode == true)
	{
		//do nothing
	}
	else
	{
		m_Grid[ID[0]].Move(-1, 0);
		m_Grid[ID[1]].Move(-1, 0);
		m_Grid[ID[2]].Move(-1, 0);
		m_Grid[ID[3]].Move(-1, 0);
	}

	if (CheckCollisions() == true)
	{
		m_Grid[ID[0]].SetPos(POS[0].x, POS[0].y);
		m_Grid[ID[1]].SetPos(POS[1].x, POS[1].y);
		m_Grid[ID[2]].SetPos(POS[2].x, POS[2].y);
		m_Grid[ID[3]].SetPos(POS[3].x, POS[3].y);
	}
}

void Grid::MoveRotate() //Rotates current block, calls: CheckCollisions
{
	sf::Vector2f POS[4];
	POS[0] = m_Grid[ID[0]].ReturnPos();
	POS[1] = m_Grid[ID[1]].ReturnPos();
	POS[2] = m_Grid[ID[2]].ReturnPos();
	POS[3] = m_Grid[ID[3]].ReturnPos();

	sf::Vector2f ADJUST[4];
	ADJUST[0].x = 0;
	ADJUST[0].y = 0;

	ADJUST[1].x = POS[0].y - POS[1].y;
	ADJUST[1].y = POS[1].x - POS[0].x;

	ADJUST[2].x = POS[0].y - POS[2].y;
	ADJUST[2].y = POS[2].x - POS[0].x;

	ADJUST[3].x = POS[0].y - POS[3].y;
	ADJUST[3].y = POS[3].x - POS[0].x;

	if (lineEliminationMode == true)
	{
		//do nothing
	}
	else
	{
		//rotate
		m_Grid[ID[0]].SetPos(POS[0].x + ADJUST[0].x, POS[0].y + ADJUST[0].y);
		m_Grid[ID[1]].SetPos(POS[0].x + ADJUST[1].x, POS[0].y + ADJUST[1].y);
		m_Grid[ID[2]].SetPos(POS[0].x + ADJUST[2].x, POS[0].y + ADJUST[2].y);
		m_Grid[ID[3]].SetPos(POS[0].x + ADJUST[3].x, POS[0].y + ADJUST[3].y);
	}

	if (CheckCollisions() == true)
	{
		m_Grid[ID[0]].SetPos(POS[0].x, POS[0].y);
		m_Grid[ID[1]].SetPos(POS[1].x, POS[1].y);
		m_Grid[ID[2]].SetPos(POS[2].x, POS[2].y);
		m_Grid[ID[3]].SetPos(POS[3].x, POS[3].y);
	}
}

void Grid::Tick() //Checks time, based on level, pushes blocks down, calls CheckCollisions, if true: reverses and calls CheckLines
{
	bool spawnedBlock = false;

	level = std::floorf((score / 200));

	if(lineEliminationMode == false)
	{
		float adaptation = (level/20);
		if (level/20 >= 0.9)
			adaptation = 0.9;
		if(lastTickTime.GetElapsedTime() >= sf::Seconds(1.0 - adaptation))
		{
			std::cout<<"TICK \n";
			sf::Vector2f POS[4];
			POS[0] = m_Grid[ID[0]].ReturnPos();
			POS[1] = m_Grid[ID[1]].ReturnPos();
			POS[2] = m_Grid[ID[2]].ReturnPos();
			POS[3] = m_Grid[ID[3]].ReturnPos();

			if(m_Grid[ID[0]].ReturnMode() == 0)
			{
				m_Grid[ID[0]].Move(0, 1);
				m_Grid[ID[1]].Move(0, 1);
				m_Grid[ID[2]].Move(0, 1);
				m_Grid[ID[3]].Move(0, 1);
			}

			if (CheckCollisions() == true)
			{
				m_Grid[ID[0]].SetPos(POS[0].x, POS[0].y);
				m_Grid[ID[1]].SetPos(POS[1].x, POS[1].y);
				m_Grid[ID[2]].SetPos(POS[2].x, POS[2].y);
				m_Grid[ID[3]].SetPos(POS[3].x, POS[3].y);

				m_Grid[ID[0]].SetMode(1);
				m_Grid[ID[1]].SetMode(1);
				m_Grid[ID[2]].SetMode(1);
				m_Grid[ID[3]].SetMode(1);
			
				if (CheckLines() == false)
				{
					SpawnBlock();
					spawnedBlock = true;
				}
				else
				{
					//
				}
			}

			if(m_Grid[ID[0]].ReturnMode() != 0 && spawnedBlock == false)
			{
				SpawnBlock();
			}

			lastTickTime.Restart();
		}
	}

	else if(lineEliminationMode == true)
	{
		if(lastTickTime.GetElapsedTime() >= sf::Seconds(1.05f))
		{
			EndEliminationMode();
		}
	}
}

void Grid::SpawnBlock() //choose next block and create current block
{
	std::cout<<"SpawnBlock() \n";
	if(lineEliminationMode != true)
	{
		//finding availible block ID's
		for(int i=0; i<180; i++)
		{
			bool triggerbreak = false;
			if(m_Grid[i].ReturnMode() == 3)
			{
				ID[0] = i;
				m_Grid[ID[0]].SetMode(0);
				triggerbreak = true;
			}
			if(triggerbreak == true)
				break;
		}
		

		for(int i=0; i<180; i++)
		{
			bool triggerbreak = false;
			if(m_Grid[i].ReturnMode() == 3)
			{
				ID[1] = i;
				m_Grid[ID[1]].SetMode(0);
				triggerbreak = true;
			}
			if(triggerbreak == true)
				break;
		}
		

		for(int i=0; i<180; i++)
		{
			bool triggerbreak = false;
			if(m_Grid[i].ReturnMode() == 3)
			{
				ID[2] = i;
				m_Grid[ID[2]].SetMode(0);
				triggerbreak = true;
			}
			if(triggerbreak == true)
				break;
		}
		

		for(int i=0; i<180; i++)
		{
			bool triggerbreak = false;
			if(m_Grid[i].ReturnMode() == 3)
			{
				ID[3] = i;
				m_Grid[ID[3]].SetMode(0);
				triggerbreak = true;
			}
			if(triggerbreak == true)
				break;
		}
		

		//choosing block type and placing blocks
		sf::Color RED(255, 0, 0, 255);
		sf::Color YELLOW(255, 255, 0, 255);
		sf::Color TEAL(0, 255, 255, 255);
		sf::Color MAGENTA(255, 0, 255, 255);
		sf::Color GREEN(0, 255, 0, 255);
		sf::Color BLUE(0, 0, 255, 255);
		sf::Color ORANGE(255, 165, 0, 255);
		std::srand(std::time(NULL));
		int random = std::rand() % 7;
		//O
		if (random == 0)
		{
			m_Grid[ID[0]].SetPos(5, 1);
			m_Grid[ID[1]].SetPos(6, 1);
			m_Grid[ID[2]].SetPos(5, 0);
			m_Grid[ID[3]].SetPos(6, 0);

			m_Grid[ID[0]].SetColor(RED);
			m_Grid[ID[1]].SetColor(RED);
			m_Grid[ID[2]].SetColor(RED);
			m_Grid[ID[3]].SetColor(RED);
		}
		//I
		if (random == 1)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(4, 0);
			m_Grid[ID[2]].SetPos(6, 0);
			m_Grid[ID[3]].SetPos(7, 0);

			m_Grid[ID[0]].SetColor(TEAL);
			m_Grid[ID[1]].SetColor(TEAL);
			m_Grid[ID[2]].SetColor(TEAL);
			m_Grid[ID[3]].SetColor(TEAL);
		}
		//J
		if (random == 2)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(4, 0);
			m_Grid[ID[2]].SetPos(6, 0);
			m_Grid[ID[3]].SetPos(6, 1);

			m_Grid[ID[0]].SetColor(BLUE);
			m_Grid[ID[1]].SetColor(BLUE);
			m_Grid[ID[2]].SetColor(BLUE);
			m_Grid[ID[3]].SetColor(BLUE);
		}
		//L
		if (random == 3)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(4, 0);
			m_Grid[ID[2]].SetPos(6, 0);
			m_Grid[ID[3]].SetPos(4, 1);

			m_Grid[ID[0]].SetColor(MAGENTA);
			m_Grid[ID[1]].SetColor(MAGENTA);
			m_Grid[ID[2]].SetColor(MAGENTA);
			m_Grid[ID[3]].SetColor(MAGENTA);
		}
		//S
		if (random == 4)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(6, 0);
			m_Grid[ID[2]].SetPos(5, 1);
			m_Grid[ID[3]].SetPos(4, 1);

			m_Grid[ID[0]].SetColor(GREEN);
			m_Grid[ID[1]].SetColor(GREEN);
			m_Grid[ID[2]].SetColor(GREEN);
			m_Grid[ID[3]].SetColor(GREEN);
		}
		//T
		if (random == 5)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(5, 1);
			m_Grid[ID[2]].SetPos(4, 0);
			m_Grid[ID[3]].SetPos(6, 0);

			m_Grid[ID[0]].SetColor(YELLOW);
			m_Grid[ID[1]].SetColor(YELLOW);
			m_Grid[ID[2]].SetColor(YELLOW);
			m_Grid[ID[3]].SetColor(YELLOW);
		}
		//Z
		if (random == 6)
		{
			m_Grid[ID[0]].SetPos(5, 0);
			m_Grid[ID[1]].SetPos(4, 0);
			m_Grid[ID[2]].SetPos(5, 1);
			m_Grid[ID[3]].SetPos(6, 1);

			m_Grid[ID[0]].SetColor(ORANGE);
			m_Grid[ID[1]].SetColor(ORANGE);
			m_Grid[ID[2]].SetColor(ORANGE);
			m_Grid[ID[3]].SetColor(ORANGE);
		}
	
		if (CheckCollisions() == true)
		{
			//game ends
		}
	}
}
	
int Grid::NextBlock() //returns next block (for UI)
{
	return 1;
}

int Grid::ReturnScore() //return score (for UI)
{
	return score;
}

int Grid::ReturnLevel() //returns level (for UI)
{
	level = std::floorf((score / 200));
	return level;
}

void Grid::StartEliminationMode() //starts block dystroying sequence
{
	std::cout<<"StartEliminationMode() \n";
	lineEliminationMode = true;
}

void Grid::EndEliminationMode() //ends block dystroying sequence, deletes lines
{
	DeleteLines();
	lineEliminationMode = false;
	std::cout<<"EndEliminationMode() \n";
}

/////////////////////
//Private Functions//
/////////////////////

bool Grid::CheckCollisions() //returns true on a collision
{

	for(int i=0; i<180; i++)
	{
		if(((m_Grid[i].ReturnPos().y > 18) || (m_Grid[i].ReturnPos().x < 0) || (m_Grid[i].ReturnPos().x > 9)) && m_Grid[i].ReturnMode() == 0)
		{
			std::cout<<"Collision w/ bottom/sides. \n";
			return true;
		}

		for(int j=0; j<180; j++)
		{
			if((m_Grid[i].ReturnPos() == m_Grid[j].ReturnPos()) && (m_Grid[i].ReturnMode() != 3) && (i != j))
			{
				std::cout<<"Collision w/ another block. \n";
				return true;
			}
		}
	}
	return false;
}

bool Grid::CheckLines() //Checks if line is filled, marks line for elimination, then calls emination mode
{
	std::cout<<"CheckLines() \n";

	bool deleteLine = false;
	int counter = 0;
	for(int i=0; i<19; i++)
	{
		for(int j=0; j<180; j++)
		{
			if(m_Grid[j].ReturnPos().y == i)
				counter++;
		}
		if (counter == 10)
		{
			for(int j=0; j<180; j++)
			{
				if(m_Grid[j].ReturnPos().y == i)
					m_Grid[j].SetMode(2);
			}
			deleteLine = true;
		}
		counter = 0;
	}
	
	if(deleteLine == true)
	{
		StartEliminationMode();
		return true;
	}
	else
	{
		return false;
	}
}

void Grid::DeleteLines() //Deletes lines marked for elimination, adds to score
{
	std::cout<<"DeleteLines() \n";

	for(int i=0; i<180; i++)
	{
		if(m_Grid[i].ReturnMode() == 2)
		{
			for(int j=0; j<180; j++)
			{
				if((m_Grid[j].ReturnPos().x == m_Grid[i].ReturnPos().x) && (m_Grid[j].ReturnPos().y <= m_Grid[i].ReturnPos().y) && (m_Grid[j].ReturnMode() == 1 || m_Grid[j].ReturnMode() == 0))
				{
					m_Grid[j].MarkMove();
				}
			}
		}
	}

	for(int i=0; i<180; i++)
	{
		if(m_Grid[i].ReturnMode() == 2)
		{
			m_Grid[i].Delete();
			score += 2.5;
		}
		if(m_Grid[i].ReturnMarkMove() != 0)
		{
			m_Grid[i].Move(0, m_Grid[i].ReturnMarkMove());
		}
	}
}