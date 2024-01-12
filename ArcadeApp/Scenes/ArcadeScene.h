#pragma once

#include "ButtonOptionsScene.h"
#include <memory>

enum eGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene : public ButtonOptionsScene
{
public:
	ArcadeScene();
	void Update(uint32_t dt) override;
	const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(eGame game);
};

