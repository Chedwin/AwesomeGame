#include "Scene3.h"
#include "Exception.h"

using namespace GAME;

Scene3::Scene3(class Window& windowRef) : Scene(windowRef) {
	OnCreate();
	boyPlayer = new Player(windowRef);
	boyPlayer->Load("resources/limbo_boy.bmp");
	
	Vec3 start(1.0f, 4.0f, 0.0f);
	boyPlayer->SetPos(start);
}

Scene3::~Scene3() {
	OnDestroy();
}

bool Scene3::OnCreate() {
	int w = sceneWindowPtr->GetWidth();
	int h = sceneWindowPtr->GetHeight();

	Matrix4 ndc = MMath::viewportNDC(w, h);
	projection = MMath::orthographic(0.0f, 10.0f,
		0.0f, 10.0f,
		0.0f, 10.0f) * ndc;

	sisterMusic = new Music();
	if (!sisterMusic->Load("resources/Sister.wav")) {
		throw exc;
		Debug::Log(EMessageType::ERROR, "Scene3", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Music could not be loaded!");
	}
	sisterMusic->SetVolume(128);
	sisterMusic->Play();

	scene03Bckgrnd = new Texture(sceneWindowPtr->GetRenderer());
	if (!scene03Bckgrnd->Load("resources/limbo_background03.bmp")) {
		Debug::Log(EMessageType::ERROR, "Scene3", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Background image could not be loaded!");
		throw exc;
	}

	return true;
}

void Scene3::OnDestroy() {
	sisterMusic->Stop();
	sisterMusic->Destroy();
	delete sisterMusic;
	sisterMusic = nullptr;

	delete boyPlayer;
	boyPlayer = nullptr;

	scene03Bckgrnd->Destroy();
	delete scene03Bckgrnd;
	scene03Bckgrnd = nullptr;
}

void Scene3::Update(const float deltaTime) {

}

void Scene3::Render() const {
	sceneWindowPtr->ClearRenderer();

	/// Draw your scene
	scene03Bckgrnd->Draw();
	boyPlayer->Render(projection);

	SDL_RenderPresent(sceneWindowPtr->GetRenderer());
}

bool Scene3::BeatScene() const {
	return false;
}

bool Scene3::GameOver() const {
	return false;
}