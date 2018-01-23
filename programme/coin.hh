#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "object.hh"
#include "sound.hh"

class Coin : public Object
{
using Object::Object;

public:
	Coin(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	virtual ~Coin();
	void Update(float dt);
};
