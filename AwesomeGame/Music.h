#ifndef MUSIC_H
#define MUSIC_H

#include "AudioFile.h"
#include <string>

/// This is called a forward declaration 
/// Geez,  I'm tired - go look it up - SSF
struct _Mix_Music;

namespace GAME {

	class Music : public AudioFile {
	public:
		Music();

		/// The usual suspects 
		Music(const Music&) = delete;
		Music(Music&&) = delete;
		Music& operator=(const Music&) = delete;
		Music& operator=(Music&&) = delete;

		~Music();

		// overriding AudioFile stuff
		virtual bool Load(const std::string& FileName) override;
		virtual void Play(const int LoopCount = 0) const override;
		virtual void SetVolume(int Volume) const override;
		virtual void Destroy() override;

		// new Music subroutines
		void Stop() const;
		void Pause() const;
		void Resume() const;
		void TogglePause() const;

	protected:
	private:
		_Mix_Music* MixMusic;
	};
}

#endif
