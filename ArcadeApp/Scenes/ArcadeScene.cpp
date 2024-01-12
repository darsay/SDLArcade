#include "ArcadeScene.h"
#include "Screen.h"
#include "Line2D.h"
#include "Color.h"
#include "App.h"

#include "GameScene.h"
#include "BreakOut.h"
#include "Tetris.h"
#include "NotImplementedScene.h"

ArcadeScene::ArcadeScene() : ButtonOptionsScene(
	{ "Tetris", "Break Out!", "Asteroids", "Pac-man" },
	{
			[this]() {App::Singleton().PushScene(GetScene(TETRIS)); },
			[this]() {App::Singleton().PushScene(GetScene(BREAK_OUT)); },
			[this]() {App::Singleton().PushScene(GetScene(ASTEROIDS)); },
			[this]() {App::Singleton().PushScene(GetScene(PACMAN)); }
		},
	Color::Cyan())
{
}


void ArcadeScene::Update(uint32_t dt)
{
}

const std::string& ArcadeScene::GetSceneName() const
{
	static std::string sceneName = "Arcade Scene";
	return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(eGame game)
{
	std::unique_ptr<Tetris> tetrisGame;
	std::unique_ptr<BreakOut> breakOutGame;

	switch (game) {
	case TETRIS:
		tetrisGame = std::make_unique<Tetris>();
		return std::make_unique<GameScene>(std::move(tetrisGame));

		break;

	case BREAK_OUT:
		breakOutGame = std::make_unique<BreakOut>();
		return  std::make_unique<GameScene>(std::move(breakOutGame));

		break;

	case ASTEROIDS:
		break;

	case PACMAN:
		break;
	}

	std::unique_ptr<NotImplementedScene> notImplementedScene = std::make_unique<NotImplementedScene>();

	return notImplementedScene;
}
