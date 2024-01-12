#include "Button.h"
#include "Screen.h"

Button::Button(const BitmapFont& bitmapFont, const Color& textColor, const Color& highlightColor):
mBitmapFont(bitmapFont), mTextColor(textColor), mHighlightColor(highlightColor),
mTitle(""), mHighLighted(false), mAction(nullptr)
{

}

void Button::Init(Vec2D topLeft, unsigned width, unsigned height)
{
	mBBox = AARectangle(topLeft, width, height);
}

void Button::Draw(Screen& screen)
{
	screen.Draw(mBitmapFont, mTitle, 
		mBitmapFont.GetDrawPosition(mTitle, mBBox, BFXA_CENTER,
			BFYA_CENTER), mTextColor);

	if(mHighLighted)
	{
		screen.Draw(mBBox, mHighlightColor);
	}
}

void Button::ExecuteAction()
{
	mAction();
}
