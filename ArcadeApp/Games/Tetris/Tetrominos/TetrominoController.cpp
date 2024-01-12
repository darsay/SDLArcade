#include "TetrominoController.h"

#include "AARectangle.h"
#include "PlayField.h"
#include "Screen.h"
#include "TetrisScore.h"

TetrominoController::TetrominoController(const Tetromino& tetromino) :
	mTetromino(tetromino),
	mColor(tetromino.color),
	mCurrentRotation(0)
{
}

void TetrominoController::Init(const PlayField& playField)
{
	mPosition = Vec2D((playField.PLAYFIELD_WIDTH / 2) - 1, 0);
	mBlocks = mTetromino.rotations[0];
	mGhostedBlock.Init(*this, playField);
}

void TetrominoController::Draw(Screen& screen, const PlayField& playField)
{
	AARectangle block = { mPosition, playField.mBlockSize, playField.mBlockSize };

	for (auto mBlock : mBlocks)
	{
		block.MoveTo(Vec2D(((mPosition.GetX() + mBlock.GetX()) * playField.mBlockSize + playField.MARGIN),
			((mPosition.GetY() + mBlock.GetY()) * playField.mBlockSize + playField.MARGIN))
		);

		screen.Draw(block, Color::Black(), true, mColor);
	}

	mGhostedBlock.Draw(screen, playField);
}

void TetrominoController::MoveLeft(PlayField& playField)
{
	for (auto block : mBlocks)
	{
		Vec2D nextPosition = mPosition + block;
		int nextX = nextPosition.GetX() - 1;
		int nextY = nextPosition.GetY();
		if (nextX < 0 || playField.mCells[nextX][nextY].isFilled)
		{
			return;
		}
	}

	mPosition = mPosition + Vec2D(-1, 0);
	mGhostedBlock.SetGhostPosition(*this, playField);
}


void TetrominoController::MoveRight(PlayField& playField)
{
	for (auto block : mBlocks)
	{
		Vec2D nextPosition = mPosition + block;
		int nextX = nextPosition.GetX() + 1;
		int nextY = nextPosition.GetY();
		if (nextX > playField.PLAYFIELD_WIDTH - 1 || playField.mCells[nextX][nextY].isFilled)
		{
			return;
		}
	}

	mPosition = mPosition + Vec2D(1, 0);
	mGhostedBlock.SetGhostPosition(*this, playField);
}


bool TetrominoController::MoveDown(PlayField& playField, TetrisScore& score)
{
	for (auto block : mBlocks)
	{
		Vec2D nextPosition = mPosition + block;
		int nextX = nextPosition.GetX();
		int nextY = nextPosition.GetY() + 1;
		if (nextY > playField.PLAYFIELD_HEIGHT - 1 || playField.mCells[nextX][nextY].isFilled)
		{
			playField.PlaceTetromino(this, score);
			return true;
		}
	}
	mPosition = mPosition + Vec2D(0, 1);
	return false;
}

void TetrominoController::Drop(PlayField& playField, TetrisScore& score)
{
	mPosition = mGhostedBlock.GetPosition();
	playField.PlaceTetromino(this, score);
}

void TetrominoController::Rotate(PlayField& playField)
{
	size_t tempRotation = (mCurrentRotation + 1) % mTetromino.rotations.size();

	for (auto& block : mTetromino.rotations[tempRotation])
	{
		Vec2D nextPosition = mPosition + block;
		int nextX = nextPosition.GetX();
		int nextY = nextPosition.GetY();

		if (nextX < 0 || nextY < 0 ||
			nextX > playField.PLAYFIELD_WIDTH - 1 || nextY > playField.PLAYFIELD_HEIGHT -1 ||
			playField.mCells[nextX][nextY].isFilled)
		{
			return;
		}
	}

	mCurrentRotation = tempRotation;
	mBlocks = mTetromino.rotations[mCurrentRotation];

	mGhostedBlock.SetBlocks(mBlocks);
	mGhostedBlock.SetGhostPosition(*this, playField);
}
