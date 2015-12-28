#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"
#include "VMath.h"
#include "MMath.h"
//#include "Window.h"
#include "Texture.h"


using namespace MATH; // Vector stuff.....

namespace GAME {
	class GameObject {
	public:
		// Using "explicit" means that the constructor will not try to typecast your arguments
		explicit GameObject(class Window& windowRef) : gameObjectWindowPtr(&windowRef) {}

		// Since this is an abstract class we're going to declare the base class destructor "virtual"
		// This allows any derived classes to override this destructor and correctly call its own appropriate destructor
		virtual ~GameObject() {}

		inline void SetPos(const Vec3& _pos) {
			pos = _pos;
		}
		inline void SetVel(const Vec3& _vel) {
			vel = _vel;
		}

		inline Vec3 GetPos() const {
			return pos;
		}

		// Delete all complier-given copy and move constructors
		GameObject(const GameObject&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(const GameObject&&) = delete;
		GameObject& operator=(GameObject&&) = delete;

		// GameObject is considered an "absrtact" class
		// You cannot create an object of type GameObject
		// This definition is merely a template for inheriting children
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float DeltaTime) = 0;
		virtual void Render(const Matrix4& projection) const = 0;

		virtual bool Load(const std::string& FileName) = 0;
		virtual bool CheckCollision(SDL_Rect* a, SDL_Rect* b) = 0;
	protected:
		// Vec3 stuff......
		Vec3 pos; // m
		Vec3 vel; // m/s
		Vec3 accel; // m/s^2
		float mass; // kg
		Window* gameObjectWindowPtr;
		SDL_Rect collider;
	};

}
#endif