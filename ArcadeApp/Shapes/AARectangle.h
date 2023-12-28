#pragma once

#include "Shape.h"
class AARectangle : public Shape
{
public:
	AARectangle();
	AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int heights);
	AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

	inline void SetTopLeftPoint(const Vec2D& topLeft) { mPoints[0] = topLeft; }
	inline void SetBottomRightPoint(const Vec2D& bottomRight) { mPoints[1] = bottomRight; }

	inline Vec2D GetTopLeft() const { return mPoints[0]; }
	inline Vec2D GetBottomRight() const { return mPoints[1]; }

	float GetWidth() const;
	float GetHeight() const;

	void MoveTo(const Vec2D& position);

	virtual Vec2D GetCenterPoint() const override;

	bool Intersects(const AARectangle& otherRect) const;
	bool ContainsPoint(const Vec2D& point) const;

	static AARectangle Inset(const AARectangle& rect, Vec2D& insets);

	virtual std::vector<Vec2D> GetPoints() const override;
};

