#pragma once

#include <string>
#include <stdint.h>
#include <GameController.h>

class Screen;

//Interface
class Scene
{
public:
	virtual ~Scene() = default;
	virtual void Init() = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& theScreen) = 0;
	virtual const std::string& GetSceneName() const = 0;

	GameController* GetGameController() { return &mGameController; }

protected:
	GameController mGameController;
};

