#pragma once

#include "Scene.h"
#include <memory>

enum eGame {
	TETRIS = 0,
	BREAK_OUT,
	ASTEROIDS,
	PACMAN,
	NUM_GAMES
};

class ArcadeScene : public Scene
{
public:
	ArcadeScene() = default;
	virtual void Init() override;
	void Update(uint32_t dt) override;
	void Draw(Screen& theScreen) override;
	const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Scene> GetScene(eGame game);
};

