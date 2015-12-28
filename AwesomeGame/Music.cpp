#include "Music.h"
#include "SDL_mixer.h"
#include "Debug.h"

using namespace GAME;

Music::Music() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

Music::~Music() {
	Destroy();
}



bool Music::Load(const std::string& FileName) {

	Destroy();
	MixMusic = Mix_LoadMUS(FileName.c_str());

	if (!MixMusic) {
		Debug::Log(EMessageType::ERROR, "Music", "Load", __TIMESTAMP__, __FILE__, __LINE__, std::string(Mix_GetError()));
		return false;
	}

	//Debug::Log(EMessageType::ERROR, std::string(Mix_GetError()), __FILE__, __LINE__);
	return true;
}

void Music::Play(const int LoopCount) const {
	Stop();
	if (Mix_PlayMusic(MixMusic, LoopCount) != 0) {
		Debug::Log(EMessageType::ERROR, "Music", "Play", __TIMESTAMP__, __FILE__, __LINE__, std::string(Mix_GetError()));
	}
}

void Music::SetVolume(const int musicVolume) const {
	Mix_VolumeMusic(musicVolume);
}

void Music::Destroy() {
	Mix_FreeMusic(MixMusic);
	MixMusic = nullptr;
}

void Music::Stop() const {
	if (Mix_PlayingMusic()) {
		Mix_HaltMusic();
	}
}

void Music::Pause() const {
	Mix_PauseMusic();
}

void Music::Resume() const {
	Mix_ResumeMusic();
}

void Music::TogglePause() const {
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}
