#ifndef Scene1_H
#define Scene1_H

#include "Scene.h"
#include "Window.h"
#include "Player.h"
#include "Texture.h"

namespace GAME {

	class Scene1 : public Scene  {
	public:
		explicit Scene1(Window& windowRef);
		virtual ~Scene1();


		/// Get rid of these
		Scene1(const Scene1&) = delete;
		Scene1(Scene1 &&) = delete;
		Scene1& operator=(const Scene1 &) = delete;
		Scene1& operator=(Scene1 &&) = delete;



		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		// Has the scene been beaten or not?
		// If so, tell GSM to advance the scene
		virtual bool BeatScene() const;

		// Determine if the player has failed based on the player's "real world" position
		virtual bool GameOver() const;
	protected:
		Texture* scene01bckgrnd;
		Music* cityMusic;
		Player* boyPlayer;
	};

}

#endif