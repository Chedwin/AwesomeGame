#include "Scene0.h"
#include "Exception.h"
#include "Debug.h"
#include "Window.h"
#include "Player.h"
#include "Music.h"
#include "SDL_mixer.h"
#include "AudioFile.h"

using namespace GAME;

Scene0::Scene0(class Window& windowRef) : 
				Scene(windowRef), backgroundImage(nullptr), 
				menuMusic(nullptr)			
{
	OnCreate(); 
}

Scene0::~Scene0() {
	OnDestroy();
}


bool Scene0::OnCreate() {

	backgroundImage = new Texture(sceneWindowPtr->GetRenderer());
	backgroundImage->Load("resources/limbo.bmp");

	menuMusic = new Music();

	if (!backgroundImage) {
		Debug::Log(EMessageType::ERROR, "Scene0", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Cannot load background image!");
		throw exc;
	}
			
	if(!menuMusic->Load("resources/Menu.wav") ) {
		Debug::Log(EMessageType::ERROR, "Scene0", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Music could not be loaded!");
		throw exc;
	}

	//Background_Tx = SDL_CreateTextureFromSurface(sceneWindowPtr->GetRenderer(), backgroundImage);
	menuMusic->SetVolume(128);
	menuMusic->Play(std::numeric_limits<int>::max());

	return true;
}

void Scene0::OnDestroy(){
	menuMusic->Stop();
	menuMusic->Destroy();
	delete menuMusic;
	menuMusic = nullptr;

	backgroundImage->Destroy();
	delete backgroundImage;
	backgroundImage = nullptr;
}

void Scene0::Update(const float deltaTime) {
	
} 


void Scene0::Render() const{
	sceneWindowPtr->ClearRenderer();

	/// Draw you scene
	backgroundImage->Draw();

	SDL_RenderPresent(sceneWindowPtr->GetRenderer());
};
