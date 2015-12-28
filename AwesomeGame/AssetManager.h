#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <string>
#include "SDL.h"

namespace GAME 
{
	class AssetManager {
		struct DrawParams{
			int x;
			int y;
			float scale;
			SDL_Rect* Clip;
			double Angle;
			SDL_Point* origin;
			SDL_RendererFlip Flip;
			SDL_Renderer* renderer;
			SDL_Surface* surface;
		};

	public:
		AssetManager();
		AssetManager(const AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		AssetManager& operator = (const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&&) = delete;
		~AssetManager();


		void Destroy();
		bool LoadAsset(SDL_Renderer* _renderer, const std::string& fileName);
		void Draw(
			int x,
			int y,
			float scale,
			SDL_Rect* Clip,
			double Angle,
			bool Center,
			SDL_RendererFlip Flip);


		void SetBlendMode(const SDL_BlendMode blend);
		void SetAlpha(const Uint8 A);
		void SetColor(const SDL_Color& SDLColor);
		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
		int GetHeight() const;
		int GetWidth() const;
		void Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip, int frameCount);
	private:
		void Draw(const DrawParams& Params) const;
		void Animate(const DrawParams& Params, int frameCount);
		SDL_Rect DrawRect;
		SDL_Point* SetOrigin(bool center, SDL_Rect* Clip);
		SDL_Texture* createdTexture;
		SDL_Renderer* renderer;
		int Width, Height;
		int frameCount;
		int previousFrame;
	};

}

#endif