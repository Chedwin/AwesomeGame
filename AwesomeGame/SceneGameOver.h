#ifndef SCENEGAMEOVER_H
#define SCENEGAMEOVER_H

#include "Scene.h"
#include "Window.h"
#include "Texture.h"

namespace GAME {

	class SceneGameOver : public Scene {
	public:
		explicit SceneGameOver(class Window& WindowRef);
		virtual ~SceneGameOver();

		/// Get rid of these
		SceneGameOver(const SceneGameOver&) = delete;
		SceneGameOver(SceneGameOver &&) = delete;
		SceneGameOver& operator=(const SceneGameOver &) = delete;
		SceneGameOver& operator=(SceneGameOver &&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;

		virtual bool BeatScene() const {
			return false;
		};
		virtual bool GameOver() const {
			return false;
		};
	protected:
		Texture* gameOverBckgrnd;
		Music* gameOverMusic;
	};

}

#endif