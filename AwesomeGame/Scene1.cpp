#include "Scene1.h"
#include "Exception.h"
#include "Debug.h"
#include "Window.h"
#include "Player.h"
#include "SDL_mixer.h"
#include "MMath.h"
#include "Keyboard.h"

using namespace GAME;
using namespace MATH;

Scene1::Scene1(class Window& windowRef) : Scene(windowRef)
{
	OnCreate();
	boyPlayer = new Player(windowRef);
	boyPlayer->Load("resources/limbo_boy.bmp");

	Vec3 start(1.0f, 3.0f, 0.0f);
	boyPlayer->SetPos(start);
}

Scene1::~Scene1() {
	OnDestroy();
}



bool Scene1::OnCreate() {
	Debug::ConsoleLog("Welcome to Scene 1!");

	/// Load Assets:

	// Correctly calculate the aspect ratio using the screen height and width
	// We're using the scene window pointer to retreive these values
	int w = sceneWindowPtr->GetWidth();
	int h = sceneWindowPtr->GetHeight();

	// Create an NDC (Normalized Device Coordinate) matrix to correctly map out the screen
	// From there, make a projection matrix to correctly map out real world coordinates to screen coordinates
	Matrix4 ndc = MMath::viewportNDC(w, h);
	projection = MMath::orthographic(0.0f, 10.0f,
									 0.0f, 10.0f,
									 0.0f, 10.0f) * ndc;

	scene01bckgrnd = new Texture(sceneWindowPtr->GetRenderer() );
	cityMusic = new Music();

	if (!scene01bckgrnd->Load("resources/limbo_background01.bmp")) {
		Debug::Log(EMessageType::ERROR, "Scene1", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Cannot load background image!");
		throw exc;
	}

	if(!cityMusic->Load("resources/City.wav")) {
		Debug::Log(EMessageType::ERROR, "Scene1", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Music could not be loaded!");
		throw exc;
	}

	cityMusic->SetVolume(128);
	cityMusic->Play(std::numeric_limits<int>::max());

	return true;
}

void Scene1::OnDestroy(){
	cityMusic->Stop();
	delete cityMusic;
	cityMusic = nullptr;

	delete boyPlayer;
	boyPlayer = nullptr;

	scene01bckgrnd->Destroy();
	delete scene01bckgrnd;
	scene01bckgrnd = nullptr;

	Debug::ConsoleLog("Scene 1 was destroyed!");
}

void Scene1::Update(const float deltaTime) {

	// KeyboardManager doesn't work
	// Found an alternative.......
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

	BeatScene();
} // end Update()


void Scene1::Render() const {
	sceneWindowPtr->ClearRenderer();

	/// Draw your scene
	scene01bckgrnd->Draw();
	boyPlayer->Render(projection);

	SDL_RenderPresent(sceneWindowPtr->GetRenderer());
};

bool Scene1::BeatScene() const {
	float finishLine = 10.0f;
	float boyTmpX = boyPlayer->GetPos().x;

	if (boyTmpX >= finishLine) {
		return true;
	}
	else {
		return false;
	}
}

bool Scene1::GameOver() const {
	float deadLine = -1.0f;
	float boyTmpX = boyPlayer->GetPos().x;

	if (boyTmpX <= deadLine) {
		return true;
	}
	else {
		return false;
	}
}