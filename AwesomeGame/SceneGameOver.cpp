#include "SceneGameOver.h"
#include "Exception.h"

using namespace GAME;

SceneGameOver::SceneGameOver(class Window& WindowRef) : Scene(WindowRef), gameOverBckgrnd(nullptr), gameOverMusic(nullptr) {
	OnCreate();
}


SceneGameOver::~SceneGameOver() {
	OnDestroy();
}


bool SceneGameOver::OnCreate() {
	gameOverBckgrnd = new Texture(sceneWindowPtr->GetRenderer());
	if (!gameOverBckgrnd->Load("resources/Limbo_GameOver.bmp")) {
		Debug::Log(EMessageType::ERROR, "SceneGameOver", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Cannot load background image!");
		throw exc;
	}

	gameOverMusic = new Music();
	if (!gameOverMusic->Load("resources/Gravity_Jump.wav")) {
		Debug::Log(EMessageType::ERROR, "SceneGameOver", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Cannot load background music!");
		throw exc;
	}
	gameOverMusic->SetVolume(128);
	gameOverMusic->Play();

	return true;
}

void SceneGameOver::OnDestroy(){
	gameOverMusic->Stop();
	gameOverMusic->Destroy();
	delete gameOverMusic;
	gameOverMusic = nullptr;

	gameOverBckgrnd->Destroy();
	delete gameOverBckgrnd;
	gameOverBckgrnd = nullptr;
}

void SceneGameOver::Update(const float deltaTime) {

}


void SceneGameOver::Render() const {
	sceneWindowPtr->ClearRenderer();

	gameOverBckgrnd->Draw();

	SDL_RenderPresent(sceneWindowPtr->GetRenderer());
};
