#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<iostream>
#include<string>
#include "sound.hh"

Sound::Sound(std::string file){

	soundEffect = Mix_LoadWAV(file.c_str());

}
Sound::~Sound(){

	Mix_FreeChunk(soundEffect);

}
