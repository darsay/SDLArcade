#pragma once

#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene : public Scene {
public:
	GameScene(std::unique_ptr<Game> optrGame);
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

	virtual const std::string& GetSceneName() const override;

private:
	std::unique_ptr<Game> mGame;
};