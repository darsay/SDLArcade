#pragma once
#include <array>
#include <vector>

#include "Color.h"
#include "TetrisScore.h"
#include "Vec2D.h"

enum TetrisGameState : int;
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
	static const unsigned int PLAYFIELD_WIDTH = 10;
	static const unsigned int PLAYFIELD_HEIGHT = 20;

	const unsigned int MARGIN = 10;

	void Init(TetrisScore& mTetrisScore);
	void Draw(Screen& screen, TetrisGameState state);
	void ResetPlayField();

	void PlaceTetromino(TetrominoController* tetromino, TetrisScore& score);

	unsigned int mBlockSize;
	Cell mCells[PLAYFIELD_WIDTH][PLAYFIELD_HEIGHT];

private:
	void CheckLines(TetrisScore& score);
	void ClearLine(unsigned int line);
	void UpdateCellsAfterLine(int line);
};

