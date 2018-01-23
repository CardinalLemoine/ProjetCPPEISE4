#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include "sound.hh"


class Entity
{
public:
	Entity(){};
	Entity(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	virtual ~Entity();
	void Draw(SDL_Renderer *renderTarget);
	SDL_Rect posRect;
	bool isEnabled;



protected:
	SDL_Rect cRect;
	SDL_Texture *texture;
	float moveSpeed;
	float frameCounter;
	float frameWidth;
	float frameHeight;
	float textureWidth;
	float posX, posY;


};
