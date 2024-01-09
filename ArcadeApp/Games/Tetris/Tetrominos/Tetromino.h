#pragma once
#include <vector>

#include "Color.h"
#include "Vec2D.h"

enum TetrominoType
{
	I = 0,
	J,
	L,
	O,
	S,
	T,
	Z,
	TETROMINO_NUM
};

struct Tetromino
{
	Color color;
	std::vector<std::array<Vec2D, 4>> rotations;
};

