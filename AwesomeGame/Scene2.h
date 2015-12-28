#ifndef SCENE2_H
#define SCENE2_H

#include "Scene.h"
#include "MMath.h"
#include "Player.h"
#include "Boulder.h"
#include "SDL_mixer.h"
#include "Window.h"
#include "Debug.h"
#include "Keyboard.h"

using namespace MATH;

namespace GAME {

	class Scene2 : public Scene {
	public:
		explicit Scene2(Window& windowRef);
		virtual ~Scene2();


		/// Get rid of these
		Scene2(const Scene2&) = delete;
		Scene2(Scene2 &&) = delete;
		Scene2& operator=(const Scene2 &) = delete;
		Scene2& operator=(Scene2 &&) = delete;


		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		virtual bool BeatScene() const;
		virtual bool GameOver() const;

		void DropBoulder();
	protected:
		Texture* scene02bckgrnd;
		Music* fortMusic;
		Player* boyPlayer;
		Boulder* boulder;
		Boulder* boulder2;

		bool boulderDropTrigger;
	};

}

#endif