#pragma once

#include "../Utils/Vec2D.h"
#include <vector>

class Shape
{
public:
	virtual ~Shape() = default;

	virtual Vec2D GetCenterPoint() const = 0;
	inline virtual std::vector<Vec2D> GetPoints() const { return mPoints; }

	void MoveBy(const Vec2D& deltaOffsset);

protected:
	std::vector<Vec2D> mPoints;

};

