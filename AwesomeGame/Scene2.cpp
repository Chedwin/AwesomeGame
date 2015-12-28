#include "Scene2.h"
#include "Exception.h"

using namespace GAME;

Scene2::Scene2(class Window& windowRef) : Scene(windowRef), boulderDropTrigger(false)
{
	OnCreate();
	boyPlayer = new Player(windowRef);
	boyPlayer->Load("resources/limbo_boy.bmp");

	boulder = new Boulder(windowRef, BOULDERTYPE::OSCILLATING);
	boulder2 = new Boulder(windowRef, BOULDERTYPE::ROLLING);

	boulder->Load("resources/boulder.bmp");
	boulder2->Load("resources/rollingBoulder.bmp");


	Vec3 bStart(5.0f, -1.0f, 0.0f);
	boulder->SetPos(bStart);

	Vec3 bStart2(7.0f, 3.5f, 0.0f);
	boulder2->SetPos(bStart2);

	Vec3 start(1.0f, 3.0f, 0.0f);
	boyPlayer->SetPos(start);

}

Scene2::~Scene2() {
	OnDestroy();
}

bool Scene2::OnCreate() {
	int w = sceneWindowPtr->GetWidth();
	int h = sceneWindowPtr->GetHeight();

	Matrix4 ndc = MMath::viewportNDC(w, h);
	projection = MMath::orthographic(0.0f, 10.0f,
									 0.0f, 10.0f,
									 0.0f, 10.0f) * ndc;

	fortMusic = new Music();

	if (!fortMusic->Load("resources/Boys_Fort.wav")) {
		Debug::Log(EMessageType::ERROR, "Scene2", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Music could not be loaded!");
		throw exc;
	}

	scene02bckgrnd = new Texture(sceneWindowPtr->GetRenderer());
	if (!scene02bckgrnd->Load("resources/limbo_background02.bmp")) {
		Debug::Log(EMessageType::ERROR, "Scene2", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Background image could not be loaded!");
		throw exc;
	}

	fortMusic->SetVolume(128);
	fortMusic->Play(std::numeric_limits<int>::max());

	return true;
}

void Scene2::OnDestroy() {
	fortMusic->Stop();
	fortMusic->Destroy();
	delete fortMusic;
	fortMusic = nullptr;

	delete boyPlayer;
	boyPlayer = nullptr;
	
	delete boulder;
	boulder = nullptr;

	delete boulder2;
	boulder2 = nullptr;

	scene02bckgrnd->Destroy();
	delete scene02bckgrnd;
	scene02bckgrnd = nullptr;

	//Debug::ConsoleLog("Scene 2 was destroyed!");
}

void Scene2::Update(const float deltaTime) {
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[Keyboard::Key::D]) {
		boyPlayer->MoveRight(deltaTime);
	}
	else if (state[Keyboard::Key::A]) {
		boyPlayer->MoveLeft(deltaTime);
	}
	else if (state[Keyboard::Key::W]) {
		boyPlayer->Jump(deltaTime);
	}	
	else {
		boyPlayer->Idle(deltaTime);
	}

	boyPlayer->Update(deltaTime);

	boulder->Update(deltaTime);
	boulder2->Update(deltaTime);


	//DropBoulder();

	//Vec3 ground(cos(deltaTime), sin(deltaTime) , 0.0f);
	//ground.print();

	BeatScene();
}

void Scene2::Render() const {
	sceneWindowPtr->ClearRenderer();

	/// Draw your scene
	scene02bckgrnd->Draw();
	boyPlayer->Render(projection);
	boulder->Render(projection);
	boulder2->Render(projection);

	SDL_RenderPresent(sceneWindowPtr->GetRenderer());
}

bool Scene2::BeatScene() const { 
	float finishLine = 10.0f;
	float boyTmpX = boyPlayer->GetPos().x;

	if (boyTmpX >= finishLine) {
		return true;
	}
	else {
		return false;
	}
}

void Scene2::DropBoulder() {

#ifndef BOULDER_DROP_POINT
#define BOULDER_DROP_POINT 5.0f
#endif

	if (boyPlayer->GetPos().x >= BOULDER_DROP_POINT && !boulderDropTrigger) {
		Vec3 bDrop(BOULDER_DROP_POINT, 9.0f, 0.0f);
		boulder->SetPos(bDrop);
		boulderDropTrigger = true;
	}

}

bool Scene2::GameOver() const {
	float deadLine = -1.0f;
	float boyTmpX = boyPlayer->GetPos().x;

	if (boyTmpX <= deadLine) {
		return true;
	}
	else {
		return false;
	}
}