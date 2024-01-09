#include "GhostedBlock.h"

#include "AARectangle.h"
#include "PlayField.h"
#include "Screen.h"
#include "TetrominoController.h"


void GhostedBlock::Init(const TetrominoController& controller, const PlayField& playField)
{
	SetBlocks(controller.GetBlocks());
	SetGhostPosition(controller, playField);
}

void GhostedBlock::Draw(Screen& screen, const PlayField& playField)
{
	AARectangle block = { mPosition, playField.mBlockSize, playField.mBlockSize };

	for (auto mBlock : mBlocks)
	{
		block.MoveTo(Vec2D(((mPosition.GetX() + mBlock.GetX()) * playField.mBlockSize + playField.MARGIN),
			((mPosition.GetY() + mBlock.GetY()) * playField.mBlockSize + playField.MARGIN))
		);

		screen.Draw(block, Color::White());
	}
}

void GhostedBlock::SetBlocks(const std::array<Vec2D, 4>& blocks)
{
	mBlocks = blocks;
}

void GhostedBlock::SetGhostPosition(const TetrominoController& controller, const PlayField& playField)
{
	Vec2D outPosition = controller.GetPosition();
	int height = controller.GetPosition().GetY();

	for (int i = 0; i + height < playField.PLAYFIELD_HEIGHT; ++i)
	{
		for (const auto& block : controller.GetBlocks())
		{
			Vec2D nextPos = controller.GetPosition() + block + Vec2D(0, i);
			int nextX = nextPos.GetX();
			int nextY = nextPos.GetY();

			if(nextY > playField.PLAYFIELD_HEIGHT -1 || playField.mCells[nextX][nextY].isFilled)
			{
				mPosition = outPosition - Vec2D(0, 1);
				return;
			}
		}

		outPosition = outPosition + Vec2D(0, 1);
	}
	mPosition = outPosition - Vec2D(0, 1);
}
