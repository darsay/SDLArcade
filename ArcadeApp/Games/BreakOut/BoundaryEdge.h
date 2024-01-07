#pragma once

#include "Vec2D.h"
#include  "Line2D.h"

enum EdgeType
{
	BOTTOM_EDGE = 0,
	TOP_EDGE,
	LEFT_EDGE,
	RIGHT_EDGE,
	NUM_EDGES
};

static const Vec2D UP_DIR = Vec2D(0, -1);
static const Vec2D DOWN_DIR = Vec2D(0, 1);
static const Vec2D LEFT_DIR = Vec2D(-1, 0);
static const Vec2D RIGHT_DIR = Vec2D(1, 0);

struct BoundaryEdge
{
	Vec2D normal;
	Line2D edge;
};

