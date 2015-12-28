#include "AudioFile.h"
#include "SDL_mixer.h"

using namespace GAME;

AudioFile::AudioFile() {
	// empty....
}
AudioFile::~AudioFile() {
	// empty....
}


void AudioFile::SetMasterVolume(const int MasterVolume) const {
	Mix_Volume(-1, MasterVolume);
}

int AudioFile::GetMasterVolume() const {
	return Mix_Volume(-1, -1);
}