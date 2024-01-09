#include "PlayField.h"

#include <algorithm>
#include <cassert>

#include "AARectangle.h"
#include "App.h"
#include "Tetrominos/OTetromino.h"
#include "Tetrominos/TetrominoController.h"


PlayField::PlayField()
{
}

void PlayField::Init()
{
	ResetPlayField();
}

void PlayField::Draw(Screen& screen)
{
	AARectangle backGround = { Vec2D(MARGIN - 1, MARGIN - 1), (mBlockSize * PLAYFIELD_WIDTH) + 2, (mBlockSize * PLAYFIELD_HEIGHT) + 2 };
	screen.Draw(backGround, Color::White());

	AARectangle cellSquare = { Vec2D(MARGIN, MARGIN), mBlockSize, mBlockSize };
	for (int i = 0; i < PLAYFIELD_WIDTH; ++i)
	{
		for (int j = 0; j < PLAYFIELD_HEIGHT; ++j)
		{
			cellSquare.MoveTo(Vec2D(MARGIN + mBlockSize * i, MARGIN + mBlockSize * j));

			Cell cell = mCells[i][j];
			if (cell.isFilled)
			{
				screen.Draw(cellSquare, Color::Black(), true, cell.color);
			}
			else
			{
				screen.Draw(cellSquare, Color(255, 255, 255, 10));
			}
		}
	}
}

void PlayField::ResetPlayField()
{
	mBlockSize = (App::Singleton().Height() - MARGIN * 2) / PLAYFIELD_HEIGHT;

	for (int i = 0; i < PLAYFIELD_WIDTH; ++i)
	{
		Cell cell = { false, Color::Red() };
		std::fill_n(mCells[i], PLAYFIELD_HEIGHT, cell);
	}
}

void PlayField::PlaceTetromino(TetrominoController* tetromino)
{
	if (tetromino == nullptr) return;

	for (const auto& block : tetromino->GetBlocks())
	{
		Vec2D placeBlockPosition = tetromino->GetPosition() + block;
		int placeX = placeBlockPosition.GetX();
		int placeY = placeBlockPosition.GetY();

		Cell& placeCell = mCells[placeX][placeY];
		placeCell.color = tetromino->GetColor();
		placeCell.color.SetAlpha(255);
		placeCell.isFilled = true;
	}

	CheckLines();
}

void PlayField::CheckLines()
{
	int lineCount = 0;
	std::vector<int> linesToClear;

	for (int i = 0; i < PLAYFIELD_HEIGHT; ++i)
	{
		bool isLineFull = true;

		for (int j = 0; j < PLAYFIELD_WIDTH; ++j)
		{
			if (!mCells[j][i].isFilled)
			{
				isLineFull = false;
				break;
			}
		}

		if (isLineFull)
		{
			linesToClear.push_back(i);
			ClearLine(i);
			++lineCount;
		}
	}

	if (!linesToClear.empty())
	{
		for (const auto& line : linesToClear)
		{
			UpdateCellsAfterLine(line);
		}
	}
	//ADD SCORE ACCORDING TO LINE COUNT
}

void PlayField::ClearLine(unsigned int line)
{
	for (int i = 0; i < PLAYFIELD_WIDTH; ++i)
	{
		mCells[i][line].isFilled = false;
	}
}

void PlayField::UpdateCellsAfterLine(int line)
{
	for (int i = line; i > 1; --i)
	{
		for (int j = 0; j < PLAYFIELD_WIDTH; ++j)
		{
			if (mCells[j][i - 1].isFilled)
			{
				mCells[j][i].isFilled = true;
				mCells[j][i].color = mCells[j][i - 1].color;
				mCells[j][i-1].isFilled = false;
			}
		}
	}
}
