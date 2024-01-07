#pragma once

#include "../Graphics/Screen.h"
#include <cstdint>
#include <vector>
#include <memory>
#include <string>

#include "InputController.h"

struct SDL_Window;
class Scene;

class App
{
public:
	static App& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t mag);
	void Run();

	inline uint32_t Width() const { return mScreen.Width(); }
	inline uint32_t Height() const { return mScreen.Height(); }

	void PushScene(std::unique_ptr<Scene> scene);
	void PopScene();
	Scene* TopScene() const;

	static const std::string& GetBasePath();
private:
	Screen mScreen;
	SDL_Window* mnotrWindow;

	std::vector<std::unique_ptr<Scene>> mSceneStack;
	InputController mInputController;
};

