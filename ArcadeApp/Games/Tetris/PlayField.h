#pragma once
#include <array>
#include <vector>

#include "Color.h"
#include "Vec2D.h"

class Screen;
class TetrominoController;

struct Cell
{
	bool isFilled;
	Color color;
};

class PlayField
{
public:
	PlayField();

	static const unsigned int PLAYFIELD_WIDTH = 10;
	static const unsigned int PLAYFIELD_HEIGHT = 20;

	const unsigned int MARGIN = 10;

	void Init();
	void Draw(Screen& screen);
	void ResetPlayField();

	void PlaceTetromino(TetrominoController* tetromino);

	unsigned int mBlockSize;
	Cell mCells[PLAYFIELD_WIDTH][PLAYFIELD_HEIGHT];

private:
	void CheckLines();
	void ClearLine(unsigned int line);
	void UpdateCellsAfterLine(int line);
};

