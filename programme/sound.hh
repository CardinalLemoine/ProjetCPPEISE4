#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<iostream>

class Sound{

public:
	//Sound();
	Sound(std::string file);
	~Sound();
	Mix_Chunk *soundEffect;
	
};
