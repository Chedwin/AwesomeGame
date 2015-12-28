#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "Vector.h"

using namespace MATH;

namespace GAME {

	class Window {
	public:
		Window();
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		~Window();

		bool Initialize();
		void Shutdown();
		void ClearRenderer() const;
		void SetWindowSize(const int Width_, const int Height_);
		void ToggleFullScreen();
		SDL_Renderer* GetRenderer() const;
		int GetWidth() const;
		int GetHeight() const;

	private:
		SDL_Window* SDLWindow;
		SDL_Renderer* SDLRenderer;
		SDL_Surface* SDLSurface;

		SDL_Rect winRect;

		bool isInitialized;
		bool isFullScreen;
	};

} /// namespace GAME

#endif