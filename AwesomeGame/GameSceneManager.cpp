#include <iostream>
#include <thread> /// New in C11
#include <cassert>
#include "GameSceneManager.h"
#include "Debug.h"
#include "Timer.h"
#include "Exception.h"
#include "Scene.h"

using namespace GAME;

/// See the header file regarding unique_ptr
std::unique_ptr<GameSceneManager> GameSceneManager::instance(nullptr);

GameSceneManager* GameSceneManager::getInstance() {
	if (instance.get() == nullptr){
		/// I originally set the unique_ptr to be null in the constructor - 
		/// reset() sets the new address
		instance.reset(new GameSceneManager());
	}
	return instance.get();
}



GameSceneManager::GameSceneManager() : windowInstance(), isRunning(false), fps(10), sceneIndex(0) {
	// pre-initialized variables here
	// just to show off our intelligence haha
}



GameSceneManager::~GameSceneManager(){
	windowInstance.Shutdown();
	isRunning = false;

	delete currentScene;
	currentScene = nullptr;
}


bool GameSceneManager::Initialize(){

	windowInstance.SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!windowInstance.Initialize()) {
		Debug::Log(EMessageType::FATAL_ERROR, "GameSceneManager", "Initialize", __TIMESTAMP__, __FILE__, __LINE__, "Failed to initialize GUI window!");
		return false;
	}

	SceneChanger(sceneIndex);

	return true;
}

// This RUN() function acts as the game loop
void GameSceneManager::Run(){
	isRunning = Initialize();
	Timer timer;
	timer.Start();

	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
}


void GameSceneManager::Update(const float deltaTime) {
	SDL_Event SDLEvent;

	while (SDL_PollEvent(&SDLEvent)) {
		if (SDLEvent.type == SDL_KEYDOWN) {
			switch (SDLEvent.key.keysym.sym) {
			case SDLK_1:
				// uses scene pointer to check if the current scene has been beaten or not
				if (currentScene->BeatScene() ) {
					AdvanceSceneWindow();
				}
				return;
			case SDLK_ESCAPE:
				// exit by pressing the "esc" key
				QuitWindowPrompt();
			}
		}

		switch (SDLEvent.type) {
			case SDL_EventType::SDL_QUIT:
				QuitWindowPrompt();
				break;
		}
	}

	if (currentScene) {
		currentScene->Update(deltaTime);
	}

	if (sceneIndex != 0 && currentScene->BeatScene()) {
		AdvanceSceneWindow();
	}

	if (currentScene->GameOver()) {
		GameOverScene();
	}

}

void GameSceneManager::Render() const {

	if (currentScene == nullptr){
		Debug::Log(EMessageType::ERROR, "GameSceneManager", "Render", __TIMESTAMP__, __FILE__, __LINE__, "No scene selected as current scene");
		// if assert is passed a null object, the program immediately stops
		// these asserts ONLY work in debug mode, NOT release mode
		assert(currentScene);
		throw exc;
	}

	currentScene->Render();
}

void GameSceneManager::QuitWindowPrompt() {
	// Implement a command prompt window for quitting
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, 0, "Cancel" }, // (flags, buttonid, text)
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, // flags
		NULL, // window
		"SDL Game", // window title
		"Are you sure you want to quit?", // message
		SDL_arraysize(buttons), // num of buttons
		buttons // buttons
	};

	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonid == 1) {
		isRunning = false;
		return;
	}
	else {
		//SDL_Log("Selection was %s", buttons[buttonid].text);
	}
}

void GameSceneManager::AdvanceSceneWindow() {
	const SDL_MessageBoxButtonData buttons[] = {
		{ 0, 0, "Cancel" }, // (flags, buttonid, text)
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" }
	};

	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, // flags
		NULL, // window
		"SDL Game", // window title
		"Advance to next scene?", // message
		SDL_arraysize(buttons), // num of buttons
		buttons // buttons
	};

	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	if (buttonid == 1) {

		// currentScene will destroy the scene it's currently on
		delete currentScene;
		currentScene = nullptr;

		// it will then "replace" its address with a new scene
		sceneIndex++;
		SceneChanger(sceneIndex);

		return;
	}
} // end AdvanceSceneWindow()

void GameSceneManager::SceneChanger(const unsigned int _levelIndex) {
	// Brute force way of changing scenes
	// Unfortunately, the sceneIndex integer does not correlate directly with the scenes themselves
	// I'll think of a sexy way to write this later.....
	switch (_levelIndex) {
	case 0:
		currentScene = new Scene0(windowInstance);
		return;
	case 1:
		currentScene = new Scene1(windowInstance);
		return;
	case 2:
		currentScene = new Scene2(windowInstance);
		return;
	case 3:
		currentScene = new Scene3(windowInstance); 
		return;
	}
}

void GameSceneManager::GameOverScene() {
	delete currentScene;
	currentScene = nullptr;

	currentScene = new SceneGameOver(windowInstance);
}
