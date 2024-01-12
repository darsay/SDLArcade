#pragma once

#include "Scene.h"
#include "Button.h"
#include <string>
#include <vector>

class Screen;

class ButtonOptionsScene: public Scene
{
public:
	ButtonOptionsScene(const std::vector<std::string>& optionsNames,
		const std::vector<Button::ButtonAction>& buttonActions, const Color& textColor);

	void Init() override;
	void Update(uint32_t dt) override;
	void Draw(Screen& theScreen) override;

private:
	void SetNextButtonHighlighted();
	void SetPreviousButtonHighlighted();
	void ExecuteCurrentButtonAction();
	void HighLightCurrentButton(int previousHighlighted);

	std::vector<Button> mButtons;
	int mHighlightedOption;
};

