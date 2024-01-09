#include "STetromino.h"

#include <array>

STetromino::STetromino()
{
	color = Color::Green();

	std::array<Vec2D, 4> rotation;

	rotation[0] = Vec2D(0, 0);
	rotation[1] = Vec2D(1, 0);
	rotation[2] = Vec2D(0, 1);
	rotation[3] = Vec2D(-1, 1);

	rotations.push_back(rotation);


	rotation[0] = Vec2D(0, 0);
	rotation[1] = Vec2D(0, 1);
	rotation[2] = Vec2D(-1, 0);
	rotation[3] = Vec2D(-1, -1);

	rotations.push_back(rotation);

	rotation[0] = Vec2D(0, 0);
	rotation[1] = Vec2D(0, -1);
	rotation[2] = Vec2D(1, -1);
	rotation[3] = Vec2D(-1, 0);

	rotations.push_back(rotation);


	rotation[0] = Vec2D(0, 0);
	rotation[1] = Vec2D(0, -1);
	rotation[2] = Vec2D(1, 0);
	rotation[3] = Vec2D(1, 1);

	rotations.push_back(rotation);
}
