#pragma once

#include "Excluder.h"

class Ball;

class LevelBoundary
{
public:
	LevelBoundary() = default;
	LevelBoundary(const AARectangle& boundary);
	bool HasCollided(const Ball& ball, BoundaryEdge& edge) const;
	const AARectangle& GetAARectangle() const { return  mIncluder.GetAARectangle(); }

private:
	bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
	Excluder mIncluder;
};

