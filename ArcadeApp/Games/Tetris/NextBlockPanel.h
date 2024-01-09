#pragma once
#include "Tetromino.h"

class Screen;

class NextBlockPanel
{
public:
	void Init();
	void Draw(Screen& screen);

	void SetNextTetromino(Tetromino tetromino);
	inline void SetShouldDrawTetromino(bool shouldDraw) { mShouldDrawTetromino = shouldDraw; }

private:
	Tetromino mNextTetromino;

	unsigned int mBlockSize;
	bool mShouldDrawTetromino;

	Vec2D mInitialBlockPosition;


	const Vec2D NEXT_PANEL_POSITION = { 150, 10 };
	const unsigned int NEXT_PANEL_HEIGHT = 40;
	const unsigned int NEXT_PANEL_WIDTH = 65;
};

