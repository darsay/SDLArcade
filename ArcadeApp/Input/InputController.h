#pragma once

#include "InputAction.h"

struct GameController;

class InputController {
public:
	InputController();
	void Init(InputAction quitAction);
	void Update(uint32_t dt);

	void SetCurrentGameController(GameController* controller);
private:
	InputAction mQuit;
	GameController* mmnoptrCurrentController;
};