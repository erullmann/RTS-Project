#pragma once
//include UI/Score trackers
#include "SFML\Graphics.hpp"
#include "Block.h"

class Grid //Creates and manages an arrray that holds tetris blocks (a class)
{
public:
	void Start(int level, int score); //provides inital setup for grid 

	void Draw(sf::RenderWindow& renderWindow); //sorts through all blocks and draws them. UI draws score and such

	void MoveDown(); //Moves current block down right away, adds to score, calls: CheckCollisions

	void MoveRight(); //Moves current block right, calls: CheckCollisions

	void MoveLeft(); //Moves current block left, calls: CheckCollisions

	void MoveRotate(); //Rotates current block, calls: CheckCollisions

	void Tick(); //Checks time, based on level, pushes blocks down, calls CheckCollisions, if true: reverses and calls CheckLines

	void SpawnBlock(); //choose next block and create current block

	int NextBlock(); //returns next block (for UI)

	int ReturnScore(); //return score (for UI)

	int ReturnLevel(); //returns level (for UI)

	void StartEliminationMode(); //starts block dystroying sequence

	void EndEliminationMode(); //ends block dystroying sequence, calls delete lines

private:
	bool CheckCollisions(); //returns true on a collision

	bool CheckLines(); //Checks if line is filled, marks line for elimination, then calls emination mode

	void DeleteLines(); //Deletes lines marked for elimination, adds to score

	bool lineEliminationMode;

	Block m_Grid[180];
	int score;
	int level;
	sf::Texture img_block;
	sf::Sprite spt_block;
	int ID[4];
	sf::Clock lastTickTime;
};