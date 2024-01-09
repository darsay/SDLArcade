#include "Tetris.h"

#include <algorithm>
#include <random>

#include "GameController.h"
#include "ITetromino.h"
#include "JTetromino.h"
#include "LTetromino.h"
#include "STetromino.h"
#include "TTetromino.h"
#include "Tetrominos/OTetromino.h"
#include "Utils.h"
#include "ZTetromino.h"

void Tetris::Init(GameController& controller)
{
	controller.ClearAll();

	ButtonAction leftKeyAction;
	leftKeyAction.key = GameController::LeftKey();
	leftKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				mCurrentTetromino->MoveLeft(mPlayField);
			}
		};

	controller.AddInputActionForKey(leftKeyAction);

	ButtonAction rightKeyAction;
	rightKeyAction.key = GameController::RightKey();
	rightKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				mCurrentTetromino->MoveRight(mPlayField);
			}
		};

	controller.AddInputActionForKey(rightKeyAction);

	ButtonAction downKeyAction;
	downKeyAction.key = GameController::DownKey();
	downKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				if (mCurrentTetromino->MoveDown(mPlayField))
				{
					UpdateTetrominoStack();
					mCurrentTetromino->Init(mPlayField);
				}
			}
		};

	controller.AddInputActionForKey(downKeyAction);

	ButtonAction upKeyAction;
	upKeyAction.key = GameController::UpKey();
	upKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if (GameController::IsPressed(state))
			{
				mCurrentTetromino->Rotate(mPlayField);
			}
		};

	controller.AddInputActionForKey(upKeyAction);

	ButtonAction dropKeyAction;
	dropKeyAction.key = GameController::ActionKey();
	dropKeyAction.action = [this](uint32_t dt, InputState state)
		{
			if (mGameState == TetrisGameState::IN_START)
			{
				StartGame();
			}
			else if (mGameState == TetrisGameState::IN_GAME)
			{
				if (GameController::IsPressed(state))
				{
					mCurrentTetromino->Drop(mPlayField);
					UpdateTetrominoStack();
					mCurrentTetromino->Init(mPlayField);
					CheckIfGameOver();
				}
			}

		};

	controller.AddInputActionForKey(dropKeyAction);


	mTimeToFall = INITIAL_TIME_TO_FALL;
	mCurrentTime = mTimeToFall;

	mTetrominos = {
		{O, OTetromino()},
		{I, ITetromino()},
		{J, JTetromino()},
		{L, LTetromino()},
		{S, STetromino()},
		{T, TTetromino()},
		{Z, ZTetromino()}
	};

	SetToInitialScreen();
}

void Tetris::Update(uint32_t dt)
{
	if (mGameState == IN_GAME)
	{
		mCurrentTime -= MillisecondsToSeconds(dt);

		if (mCurrentTime < 0)
		{
			mCurrentTime = mTimeToFall;


			if (mCurrentTetromino->MoveDown(mPlayField))
			{
				UpdateTetrominoStack();
				mCurrentTetromino->Init(mPlayField);
				CheckIfGameOver();
			}

		}
	}
}

void Tetris::Draw(Screen& screen)
{
	mPlayField.Draw(screen);
	mNextBlockPanel.Draw(screen);

	if (mGameState == TetrisGameState::IN_GAME)
	{
		mCurrentTetromino->Draw(screen, mPlayField);
	}

}

void Tetris::ResetGame()
{
	mGameState = TetrisGameState::IN_START;
	mPlayField.ResetPlayField();
	mTetrominosStack.erase(mTetrominosStack.begin(), mTetrominosStack.end());
}

const std::string& Tetris::GetName() const
{
	static std::string name = "Tetris";
	return name;
}

void Tetris::StartGame()
{
	mGameState = TetrisGameState::IN_GAME;

	FillStack();
	UpdateTetrominoStack();

	mCurrentTetromino->Init(mPlayField);
	mNextBlockPanel.Init();
}

void Tetris::SetToInitialScreen()
{
	mGameState = TetrisGameState::IN_START;
	mNextBlockPanel.SetShouldDrawTetromino(false);
	ResetGame();
}

void Tetris::CheckIfGameOver()
{
	for (const auto& block : mCurrentTetromino->GetBlocks())
	{
		int x = mCurrentTetromino->GetPosition().GetX() + block.GetX();
		int y = mCurrentTetromino->GetPosition().GetY() + block.GetY();

		if(y < 0 || mPlayField.mCells[x][y].isFilled)
		{
			GameOver();
		}
	}
}

void Tetris::GameOver()
{
	SetToInitialScreen();
}

void Tetris::FillStack()
{
	for (const auto& tetromino : mTetrominos)
	{
		mTetrominosStack.push_back(tetromino.first);
	}

	auto rng = std::default_random_engine{};
	std::shuffle(mTetrominosStack.begin(), mTetrominosStack.end(), rng);
}

void Tetris::UpdateTetrominoStack()
{
	if (mCurrentTetromino == nullptr)
	{
		mCurrentTetromino = new TetrominoController(mTetrominos[mTetrominosStack.back()]);
		mTetrominosStack.pop_back();
	}
	else
	{
		delete mCurrentTetromino;
		mCurrentTetromino = nullptr;
		mCurrentTetromino = new TetrominoController(mNextTetromino);
	}


	mNextTetromino = mTetrominos[mTetrominosStack.back()];
	mTetrominosStack.pop_back();

	if (mTetrominosStack.empty())
	{
		FillStack();
	}

	mNextBlockPanel.SetNextTetromino(mNextTetromino);

}
