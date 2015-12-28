#ifndef SCENE3_H
#define SCENE3_H

#include "Scene.h"
#include"Player.h"
#include "Texture.h"
#include "SDL_mixer.h"
#include "Window.h"
#include "MMath.h"
#include "Debug.h"

namespace GAME {

	class Scene3 : public Scene {
	public:
		explicit Scene3(Window& windowRef);
		virtual ~Scene3();


		/// Get rid of these
		Scene3(const Scene3&) = delete;
		Scene3(Scene3 &&) = delete;
		Scene3& operator=(const Scene3 &) = delete;
		Scene3& operator=(Scene3 &&) = delete;


		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		virtual bool BeatScene() const;
		virtual bool GameOver() const;
	protected:
		Texture* scene03Bckgrnd;
		Player* boyPlayer;
		Music* sisterMusic;
	};

}

#endif