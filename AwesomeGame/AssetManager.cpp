#include "AssetManager.h"
#include "SDL_image.h"
#include "Debug.h"

using namespace GAME;

AssetManager::AssetManager() :createdTexture(nullptr), Width(0), Height(0), frameCount(0), previousFrame(0){}

//calls the Destroy method when object goes out of scope
AssetManager::~AssetManager(){
	Destroy();
}

//Cleans up the elements within this class
void AssetManager::Destroy(){
	SDL_DestroyTexture(createdTexture);
	delete createdTexture;
	delete renderer;
	createdTexture = nullptr;
	renderer = nullptr;
}

//Loads the image and returns true/false depending on if the image loads correctly
//Call in the scene initialization method
bool AssetManager::LoadAsset(SDL_Renderer* _renderer, const std::string& fileName){
	Destroy();
	renderer = _renderer;
	SDL_Surface* loadedAsset = IMG_Load(fileName.c_str());
	if (!loadedAsset){
		//Debug::Log(EMessageType::ERROR, "Failed to load" + fileName + "! SDL Image Error:" + IMG_GetError(), __FILE__, __LINE__);
		return false;
	}
	else{
		createdTexture = SDL_CreateTextureFromSurface(renderer, loadedAsset);
		Width = loadedAsset->w;
		Height = loadedAsset->h;
		if (!createdTexture){
			//Debug::Log(EMessageType::ERROR, "Failed to creat texture from " + fileName + ". SDL Error: " + SDL_GetError(), __FILE__, __LINE__);
		}
		else{
			SDL_FreeSurface(loadedAsset);
			loadedAsset = nullptr;
			return true;
		}
	}
}

//Sets the draw parameters and calls the main draw method
//Call in the Scene Render method
void AssetManager::Draw(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip){
	DrawParams Params = DrawParams{ x, y, scale, Clip, Angle, SetOrigin(Center, Clip), Flip };
	Draw(Params);
}

//Sets the origin of the asset
//If true is passed the origin will be set to the center 
SDL_Point* AssetManager::SetOrigin(bool center, SDL_Rect* Clip){
	if (center)
		return (new SDL_Point{ Clip->w / 2, Clip->h / 2 });
	else
		return (new SDL_Point{ 0, 0 });
}

//Draws a STATIC image to the scene based on the passed in parameters
//Overloaded draw method
void AssetManager::Draw(const DrawParams& Params) const{
	SDL_Rect DrawRect = {
		(int)(Params.x + (-Width * (Params.scale - 1.0f) * 0.5f)),
		(int)(Params.y + (-Height * (Params.scale - 1.0f) * 0.5f)),
		(int)(Width * Params.scale),
		(int)(Height * Params.scale) };
	if (Params.Clip){
		DrawRect.w = Params.Clip->w;
		DrawRect.h = Params.Clip->h;
	}
	SDL_RenderCopyEx(renderer, createdTexture, NULL, &DrawRect, Params.Angle, Params.origin, Params.Flip);

}

//Sets the specified blend mode for the asset
//Call after LoadAsset in the Scene Initialization method
//NOTE: Passing in SDL_BLENDMODE_BLEND will allow the alpha channel of an png _
//image to be used in rendering (the sprite will use the transparent background)
//ANOTHER NOTE: Insert the following line of code in the program initialization after the windos is created:
//SDL_SetRenderDrawBlendMode(window.GetRenderer(), SDL_BLENDMODE_BLEND);
//This allows the render to accept the texture's blend mode
void AssetManager::SetBlendMode(const SDL_BlendMode blend){
	SDL_SetTextureBlendMode(createdTexture, blend);
}

//Sets the alpha (transparancy) of the sprite
//Range: 0-255 (255 being opaque)
void AssetManager::SetAlpha(const Uint8 A){
	SDL_SetTextureAlphaMod(createdTexture, A);
}

//Sets a colour overlay to the image
void AssetManager::SetColor(const SDL_Color& SDLColor){
	SetColor(SDLColor.r, SDLColor.g, SDLColor.b, SDLColor.a);
}
//Sets a colour overlay to the image
void AssetManager::SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a){
	SDL_SetTextureColorMod(createdTexture, r, g, b);
	SDL_SetTextureAlphaMod(createdTexture, a);
}

//returns the height of the image
int AssetManager::GetHeight() const{
	return Height;
}

//returns the width of the image
int AssetManager::GetWidth() const{
	return Width;
}

//Sets the parameters to draw an animated spritesheet and calls the main animate method
//frameCount is an integer value for the number of frames to be parsed HORIZONTALLY
//Call in the Scene Render method
void AssetManager::Animate(int x, int y, float scale, SDL_Rect* Clip, double Angle, bool Center, SDL_RendererFlip Flip, int frameCount){
	DrawParams Params = DrawParams{ x, y, scale, Clip, Angle, SetOrigin(Center, Clip), Flip };
	Animate(Params, frameCount);
}

//Cuts the spritesheet based on the given frameCount and updates each iteration
//ClipRect is the "frame" that allows only the current frame to appear
//DrawRect moves the image underneath based on the currrent frame and the width of each frame 
void AssetManager::Animate(const DrawParams& Params, int frameCount) {
	SDL_Rect ClipRect = {
		(Params.x + ((-Width / frameCount) * (Params.scale - 1.0f) * 0.5f)),
		(Params.y + (-Height * (Params.scale - 1.0f) * 0.5f)),
		((Width / frameCount)  * Params.scale),
		(Height * Params.scale) };

	if (previousFrame + 1 > frameCount)
		previousFrame = 0;

	SDL_Rect DrawRect = { (previousFrame *((Width / frameCount))),
		0.0f,
		(Width / frameCount),
		Height };
	previousFrame = previousFrame + 1;
	SDL_RenderCopyEx(renderer, createdTexture, &DrawRect, &ClipRect, Params.Angle, Params.origin, Params.Flip);
}