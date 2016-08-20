#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>


namespace pong {


enum Sound {
	SOUND_BA,
	SOUND_SPIT
};


class Audio {
public:
	Audio();
	~Audio();

	void playMusic();
	void playSound(Sound sound);
	void pauseMusic();
	void haltMusic();

private:
	void loadMedia();
	Mix_Music *music_ = nullptr;

	Mix_Chunk *ba_sound_ = nullptr;
	Mix_Chunk *spit_sound_ = nullptr;

};

}//namespace pong