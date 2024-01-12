#include "App.h"
#include <SDL.h>
#include <iostream>
#include "ArcadeScene.h"
#include <memory>
#include <cassert>

App& App::Singleton()
{
	static App theApp;
	return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
	if (!mFont.Load("ArcadeFont"))
	{
		std::cout << "Could not load font!" << std::endl;
		return false;
	}

	mnotrWindow = mScreen.Init(width, height, mag);

	std::unique_ptr<ArcadeScene> arcadeScene = std::make_unique<ArcadeScene>();

	PushScene(std::move(arcadeScene));

	return mnotrWindow != nullptr;
}

void App::Run()
{
	if (!mnotrWindow) {
		return;
	}

	SDL_Event sdlEvent;
	bool running = true;

	uint32_t lastTick = SDL_GetTicks();
	uint32_t currentTick = lastTick;

	uint32_t dt = 10;
	uint32_t accumulator = 0;

	mInputController.Init([&running](uint32_t dt, InputState state) {
		running = false;
		});

	while (running)
	{
		currentTick = SDL_GetTicks();
		uint32_t frameTime = currentTick - lastTick;

		if (frameTime > 300) {
			frameTime = 300;
		}

		lastTick = currentTick;

		accumulator += frameTime;

		//INPUT
		mInputController.Update(dt);

		Scene* topScene = TopScene();
		assert(topScene && "Why don't we have top scene?");

		if (topScene) {
			while (accumulator >= dt)
			{
				//UPDATE SCENE BY DT
				topScene->Update(dt);

				//std::cout << "Delta time step: " << dt << std::endl;
				accumulator -= dt;

			}

			topScene->Draw(mScreen);
		}

		mScreen.SwapScreens();
	}

}

void App::PushScene(std::unique_ptr<Scene> scene)
{
	assert(scene && "Don't push nullptr");
	if (!scene)
	{
		return;
	}

	scene->Init();
	mInputController.SetCurrentGameController(scene->GetGameController());
	mSceneStack.emplace_back(std::move(scene));
	SDL_SetWindowTitle(mnotrWindow, TopScene()->GetSceneName().c_str());
}

void App::PopScene()
{
	if (mSceneStack.size() > 1) {
		mSceneStack.pop_back();
	}

	if (TopScene()) {
		mInputController.SetCurrentGameController(TopScene()->GetGameController());
		SDL_SetWindowTitle(mnotrWindow, TopScene()->GetSceneName().c_str());
	}


}

Scene* App::TopScene() const
{
	if (mSceneStack.empty()) {
		return nullptr;
	}

	return mSceneStack.back().get();
}

const std::string& App::GetBasePath()
{
	static std::string basePath = SDL_GetBasePath();
	return basePath;
}
