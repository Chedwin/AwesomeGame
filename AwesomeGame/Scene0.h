#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"
#include "Texture.h"

namespace GAME {

	class Scene0 : public Scene  {
	public:
		explicit Scene0(Window& windowRef);
		virtual ~Scene0();


		/// Get rid of these
		Scene0(const Scene0&) = delete;
		Scene0(Scene0 &&) = delete;
		Scene0& operator=(const Scene0 &) = delete;
		Scene0& operator=(Scene0 &&) = delete;


		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		// default this scene as "beaten"
		virtual bool BeatScene() const { 
			return true; 
		};
		virtual bool GameOver() const {
			return false;
		};

	private:
		Texture* backgroundImage;
		Music* menuMusic;

	};

}

#endif