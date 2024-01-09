#pragma once
#include <array>

#include "Vec2D.h"

class Screen;
class PlayField;
class TetrominoController;

class GhostedBlock
{
public:
	GhostedBlock() = default;
	void Init(const TetrominoController& controller, const PlayField& playField);
	void Draw(Screen& screen, const PlayField& playField);

	void SetBlocks(const std::array<Vec2D, 4>& blocks);
	void SetGhostPosition(const TetrominoController& controller, const PlayField& playField);

	inline Vec2D GetPosition() const { return mPosition; }
private:
	Vec2D mPosition;
	std::array<Vec2D, 4> mBlocks;
};

