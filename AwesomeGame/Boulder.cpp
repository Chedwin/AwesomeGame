#include "Debug.h"
#include "Boulder.h"
#include "Window.h"

using namespace GAME;
using namespace MATH;

Boulder::Boulder(class Window& windowRef, BOULDERTYPE bldType) : GameObject(windowRef), boulderType(bldType) {
	OnCreate();
}

Boulder::~Boulder(){
	OnDestroy();
}

bool Boulder::Load(const std::string& FileName){
	if (!boulderTexture->Load(FileName)){
		return false;
	}
	return true;
}

bool Boulder::OnCreate() {
	boulderTexture = new Texture(gameObjectWindowPtr->GetRenderer());
	return true;
}

void Boulder::OnDestroy() {
	boulderTexture->Destroy(); 
	delete boulderTexture; 
}

void Boulder::Update(const float deltaTime) {
	if (boulderType == BOULDERTYPE::OSCILLATING) {
		static float time = 0.0f;
		time += deltaTime;
		const float amplitude = 2.0f;
		pos.y = amplitude * sin(time) + 6.0f;
	} 
	else if (BOULDERTYPE::ROLLING) {
		
	}
}

void Boulder::Render(const Matrix4& projection) const  {
	Vec3 screenCoords = projection * pos;
	boulderTexture->Draw(int(screenCoords.x), int(screenCoords.y) );
}
