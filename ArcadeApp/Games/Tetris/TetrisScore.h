#pragma once
#include "AARectangle.h"
#include "BitmapFont.h"
#include "Vec2D.h"


class Screen;

class TetrisScore
{
public:
	TetrisScore();
	void Init();
	void Draw(Screen& screen);

	inline void ResetScore() { mScore = 0; }
	void UpdateScore(int numLines);


private:
	int mScore;

	const Vec2D SCORE_DISPLAY_POSITION = { 150, 60 };
	const  int LINE_SCORE = 100;
	const unsigned int SCORE_DISPLAY_HEIGHT = 40;
	const unsigned int SCORE_DISPLAY_WIDTH = 65;
};

