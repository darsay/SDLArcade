#pragma once
#include <array>
#include <cstdint>

#include "Vec2D.h"
#include "Color.h"
#include "GhostedBlock.h"
#include "Tetromino.h"

class Screen;
class PlayField;



class TetrominoController
{
public:
	TetrominoController(const Tetromino& tetromino);
	virtual ~TetrominoController() = default;

	virtual void Init(const PlayField& playField);
	void Update(const uint32_t dt);
	void Draw(Screen& screen, const PlayField& playField);

	void MoveLeft(PlayField& playField);
	void MoveRight(PlayField& playField);
	bool MoveDown(PlayField& playField);
	void Drop(PlayField& playField);

	void Rotate(PlayField& playField);
	std::array<Vec2D, 4> GetBlocks() const { return mBlocks; }
	Color GetColor() const { return mColor; }
	Vec2D GetPosition() const { return mPosition; }

protected:
	Vec2D mPosition;
	Color mColor;
	Tetromino mTetromino;
	std::array<Vec2D, 4> mBlocks;
	size_t mCurrentRotation;

	GhostedBlock mGhostedBlock;
};

