#ifndef BOULDER_H
#define BOULDER_H

#include "Texture.h"
#include "VMath.h"
#include "GameObject.h"
#include "Window.h"

using namespace MATH;

namespace GAME {

	enum BOULDERTYPE : unsigned int {
		OSCILLATING,
		ROLLING
	};

	class Boulder : public GameObject {
	protected:
		Texture* boulderTexture;
		BOULDERTYPE boulderType;
	public:
		Boulder(class Window& windowRef, BOULDERTYPE bldType);
		virtual ~Boulder();

		Boulder(const Boulder&) = delete;
		Boulder(Boulder&&) = delete;
		Boulder& operator=(const Boulder&&) = delete;
		Boulder& operator=(Boulder&&) = delete;

		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projection) const;

		virtual bool Load(const std::string& FileName);
		virtual bool CheckCollision(SDL_Rect* a, SDL_Rect* b) { return false; }
	};

}

#endif