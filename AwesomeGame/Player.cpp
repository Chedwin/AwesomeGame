#include "Player.h"
#include "Exception.h"
#include "Debug.h"
using namespace GAME;


Player::Player(class Window& windowRef) : GameObject(windowRef), playerState(PlayerState::IDLE) {
	OnCreate();
}
Player::~Player(){
	OnDestroy();
}



bool Player::Load(const std::string& FileName){
	if (!playerTexture->Load(FileName)) {
		Debug::Log(EMessageType::ERROR, "Player", "OnCreate", __TIMESTAMP__, __FILE__, __LINE__, "ERROR: Cannot load boy image!");
		return false;
	}
	return true;
}

bool Player::OnCreate() {
	playerTexture = new Texture(gameObjectWindowPtr->GetRenderer());

	// initialize the collider on player
	collider.w = playerTexture->GetWidth();
	collider.h = playerTexture->GetHeight();

	return true;
}

void Player::OnDestroy() {
	playerTexture->Destroy();
	delete playerTexture;
}

void Player::Update(const float deltaTime) 
{
	switch (playerState) {
	case PlayerState::RIGHT:
		MoveRight(deltaTime);
		return;
	case PlayerState::LEFT:
		MoveLeft(deltaTime);
		return;
	case PlayerState::JUMPING:
		Jump(deltaTime);
		return;
	default:
		Idle(deltaTime);
		return;
	}

}

void Player::Render(const Matrix4& projection) const 
{
	Vec3 screenCoords = projection * pos;

	switch (playerState) {
	case PlayerState::RIGHT:
		playerTexture->Draw(int(screenCoords.x), int(screenCoords.y), 1.0f, nullptr, 0.0f, nullptr, playerFaceDir);
		return;
	case PlayerState::LEFT:
		playerTexture->Draw(int(screenCoords.x), int(screenCoords.y), 1.0f, nullptr, 0.0f, nullptr, playerFaceDir);
		return;
	default:
		playerTexture->Draw(int(screenCoords.x), int(screenCoords.y), 1.0f, nullptr, 0.0f, nullptr, playerFaceDir);
		return;
	}
}



/// Movement subroutines
void Player::Idle(const float deltaTime) {
	playerState = PlayerState::IDLE;

	if (pos.y > 3.0f) {
		pos.y -= (vel.y * deltaTime) + (0.5f * GRAVITY * deltaTime * deltaTime);
	}
	collider.y = pos.y;
}

void Player::Jump(const float deltaTime) 
{
	playerState = PlayerState::JUMPING;
	accel.y = GRAVITY;
	vel.y = accel.y * deltaTime;
	pos.y += (vel.y * 5.0f * deltaTime) + (0.5f * GRAVITY * deltaTime * deltaTime);
	collider.y = pos.y;
}

void Player::MoveRight(const float deltaTime) 
{
	playerState = PlayerState::RIGHT; 
	playerFaceDir = SDL_RendererFlip::SDL_FLIP_NONE;

	accel.x = 0.3f;
	vel.x += accel.x * deltaTime;
	pos.x += (vel.x * deltaTime) + (0.5f * accel.x * deltaTime * deltaTime);
	collider.x = pos.x;
}

void Player::MoveLeft(const float deltaTime) 
{
	playerState = PlayerState::LEFT;
	playerFaceDir = SDL_RendererFlip::SDL_FLIP_HORIZONTAL;

	accel.x = -0.3f;
	vel.x -= accel.x * deltaTime;
	pos.x -= (vel.x * deltaTime) + (0.5f * accel.x * deltaTime * deltaTime);
	collider.x = pos.x;
}

bool Player::CheckCollision(SDL_Rect* a, SDL_Rect* b) {
	if (SDL_HasIntersection(a, b)) {
		return true;
	} else {
		return false;
	}
}