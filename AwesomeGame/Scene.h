#ifndef SCENE_H
#define SCENE_H

#include "Timer.h"
#include "Music.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

namespace GAME {

	class Scene {
	public:
		// explicit means that the complier will not try to typecast the argument for the constructor
		// these two subroutines are "concrete" or real
		explicit Scene(class Window& WindowRef) : sceneWindowPtr(&WindowRef) {}

		// Having this virtual destructor means that any Scene* ptr will point its appropriate destructor
		// and not this abstract one
		virtual ~Scene() {}

		Scene(const Scene&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(const Scene&&) = delete;
		Scene& operator=(Scene&&) = delete;

		// Scene is considered an "absrtact" class
		// You cannot create an object of type Scene
		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(const float DeltaTime) = 0;
		virtual void Render() const = 0;

		virtual bool BeatScene() const = 0;
		virtual bool GameOver() const = 0;
	protected:
		Window* sceneWindowPtr;

		Matrix4 projection;
	};

}
#endif