#pragma once
#include <cstdint>
#include <string>

#include "Game.h"
class Screen;
class GameController;

class Ateroids : public Game
{
public:
	void Init(GameController& controller) override;
	void Update(uint32_t dt) override;
	void Draw(Screen& screen) override;

	void ResetGame();
	const std::string& GetName() const override;

private:
};

