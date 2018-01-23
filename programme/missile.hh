#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "object.hh"

class Missile : public Object
{
using Object::Object;

public:
	Missile(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY);
	virtual ~Missile();

	void Update(float dt);
};
