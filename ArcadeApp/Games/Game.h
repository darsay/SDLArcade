#pragma once

#include <string>

class GameController;
class Screen;

class Game {
public:
	virtual ~Game() = default;
	virtual void Init(GameController& controller) = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& screen) = 0;
	virtual const std::string& GetName() const = 0;
};