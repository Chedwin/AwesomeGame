#ifndef PLAYER_H
#define PLAYER_H

#include "Texture.h"
#include "VMath.h"
#include "GameObject.h"
#include "Window.h"

namespace GAME {

	enum PlayerState : unsigned int {
		JUMPING,
		RIGHT,
		LEFT,
		IDLE
	};

	class Player : public GameObject {
	protected:
		Texture* playerTexture;
		SDL_RendererFlip playerFaceDir;
	public:
		Player(class Window& windowRef);
		virtual ~Player();

		Player(const Player&) = delete;
		Player(Player&&) = delete;
		Player& operator=(const Player&&) = delete;
		Player& operator=(Player&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projection) const;

		virtual bool Load(const std::string& FileName);
		virtual bool CheckCollision(SDL_Rect* a, SDL_Rect* b);

		void Jump(const float deltaTime);
		void MoveLeft(const float deltaTime);
		void MoveRight(const float deltaTime);
		void Idle(const float deltaTime);

		PlayerState playerState;
	};

}

#endif