#include "NextBlockPanel.h"
#include "AARectangle.h"
#include "Screen.h"
#include <array>

void NextBlockPanel::Init()
{
	mBlockSize = NEXT_PANEL_WIDTH / 5;
	mInitialBlockPosition = NEXT_PANEL_POSITION + Vec2D(static_cast<float>(NEXT_PANEL_WIDTH / 2) - mBlockSize, static_cast<float>(NEXT_PANEL_HEIGHT / 2) - mBlockSize);
	mShouldDrawTetromino = true;
}

void NextBlockPanel::Draw(Screen& screen)
{
	AARectangle outline = { NEXT_PANEL_POSITION, NEXT_PANEL_WIDTH, NEXT_PANEL_HEIGHT };
	screen.Draw(outline, Color::White());

	if(mNextTetromino.rotations.empty() || !mShouldDrawTetromino)
	{
		return;
	}

	AARectangle block = { Vec2D::Zero, mBlockSize, mBlockSize};

	for (auto mBlock : mNextTetromino.rotations[0])
	{
		block.MoveTo(Vec2D(((mInitialBlockPosition.GetX() + mBlock.GetX() * mBlockSize)),
			((mInitialBlockPosition.GetY() + mBlock.GetY() * mBlockSize) ))
		);

		screen.Draw(block, Color::Black(), true, mNextTetromino.color);
	}
}

void NextBlockPanel::SetNextTetromino(Tetromino tetromino)
{
	mNextTetromino = tetromino;
}
