#include "TetrisScore.h"
#include "AARectangle.h"
#include "App.h"


TetrisScore::TetrisScore():mScore(0)
{
}

void TetrisScore::Init()
{
}

void TetrisScore::Draw(Screen& screen)
{
	AARectangle outline = AARectangle(SCORE_DISPLAY_POSITION, SCORE_DISPLAY_WIDTH, SCORE_DISPLAY_HEIGHT);

	//screen.Draw(outline, Color::White());

	const BitmapFont font = App::Singleton().GetFont();

	Vec2D scoreTitle = font.GetDrawPosition("Score:", outline, BFXA_CENTER, BFYA_TOP);

	screen.Draw(font, "Score:", scoreTitle);

	Vec2D textPos = font.GetDrawPosition(std::to_string(mScore), outline, BFXA_CENTER, BFYA_CENTER);
	screen.Draw(font, std::to_string(mScore), textPos);
}

void TetrisScore::UpdateScore(int numLines)
{
	mScore += LINE_SCORE + (numLines -1)*2;

	if(numLines == 4)
	{
		mScore += 1000;
	}
}


