#include "ArcadeScene.h"
#include "Screen.h"
#include "Line2D.h"
#include "AARectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Color.h"
#include "GameController.h"

void ArcadeScene::Init()
{
	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t dt, InputState state) {

		if (!GameController::IsPressed(state)) {
			std::cout << "Action Button was pressed" << std::endl;
		}
	};

	mGameController.AddInputActionForKey(action);

	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position)
		{
			if (GameController::IsPressed(state)) {
				std::cout << "Left Mouse Button was pressed" << std::endl;
			}
		};

	mGameController.AddMouseButtonAction(mouseAction);

	mGameController.SetMouseMovedAction([](const MousePosition& mousePosition) {
		std::cout << "Mouse Position x: " << mousePosition.xPos << "Mouse Position y: " << mousePosition.yPos << std::endl;
		});
}

void ArcadeScene::Update(uint32_t dt)
{
}

void ArcadeScene::Draw(Screen& theScreen)
{
	Line2D line = { Vec2D(0,0), Vec2D(theScreen.Width(), theScreen.Height()) };
	Triangle triangle = { Vec2D(60, 10), Vec2D(10,110), Vec2D(110, 110) };
	AARectangle rect = { Vec2D(theScreen.Width() / 2 - 25, theScreen.Height() / 2 - 25), 50, 50 };
	Circle circle = { Vec2D(theScreen.Width() / 2 , theScreen.Height() / 2), 50 };

	theScreen.Draw(triangle, Color::Red(), true, Color::Red());
	theScreen.Draw(rect, Color::Green(), true, Color::Green());
	theScreen.Draw(circle, Color(0, 0, 255, 56), true, Color(0, 0, 255, 56));

	theScreen.Draw(line, Color::Yellow());
}

const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	switch (game) {
	case TETRIS:
		break;

	case BREAK_OUT:
		break;

	case ASTEROIDS:
		break;

	case PACMAN:
		break;

	default:
		break;
	}

	return nullptr;
}
