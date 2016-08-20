#include "audio.h"
#include <iostream>

namespace pong {


Audio::Audio()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	this->loadMedia();
}

void Audio::loadMedia()
{

	music_ = Mix_LoadMUS("data/WahWahMusic.wav");
	if (music_ == nullptr) {
		std::cerr << "Music load failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	ba_sound_ = Mix_LoadWAV("data/baSound.wav");
	spit_sound_ = Mix_LoadWAV("data/spitSound.wav");

	if (ba_sound_ == nullptr || spit_sound_ == nullptr) {
		std::cerr << "Sound load failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}


void Audio::playMusic()
{
	//If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music_, -1);
	}
	//If music is being played
	else
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
	}
}

void Audio::playSound(Sound sound)
{
	switch (sound) {
	case(SOUND_BA):
		Mix_PlayChannel(-1, ba_sound_, 0);
		break;
	case(SOUND_SPIT):
		Mix_PlayChannel(-1, spit_sound_, 0);
		break;
	}
}


void Audio::pauseMusic() 
{
	Mix_PauseMusic();
}

void Audio::haltMusic() 
{
	Mix_HaltMusic();
}

Audio::~Audio() 
{
	Mix_FreeMusic(music_);
	Mix_FreeChunk(ba_sound_);
	Mix_FreeChunk(spit_sound_);
	music_ = nullptr;
	ba_sound_ = nullptr;
	spit_sound_ = nullptr;
	Mix_Quit();

}


}