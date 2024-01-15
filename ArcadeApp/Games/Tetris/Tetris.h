#pragma once
#include <unordered_map>

#include "Game.h"
#include "NextBlockPanel.h"
#include "PlayField.h"
#include "TetrisScore.h"
#include "TetrominoController.h"

enum TetrisGameState
{
	IN_START = 0,
	IN_GAME,
	IN_LOSE_SCREEN,
};

class Tetris : public Game
{
public:
	void Init(GameController& controller) override;
	void Update(uint32_t dt) override;
	void Draw(Screen& screen) override;

	void ResetGame();
	const std::string& GetName() const override;

	inline float GetTimeToFall() const { return mTimeToFall; }
	
private:
	PlayField mPlayField;
	TetrisScore mTetrisScore;
	TetrominoController* mCurrentTetromino;
	NextBlockPanel mNextBlockPanel;

	float mTimeToFall;
	float mCurrentTime;

	std::unordered_map<TetrominoType, Tetromino> mTetrominos;
	std::vector<TetrominoType> mTetrominosStack;
	Tetromino mNextTetromino;
	int mLevel;
	void CheckLevel();

	TetrisGameState mGameState;

	const uint32_t INITIAL_TIME_TO_FALL = 1;

	void StartGame();
	void SetToInitialScreen();
	void CheckIfGameOver();
	void GameOver();
	void FillStack();
	void UpdateTetrominoStack();
	
};