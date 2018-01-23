#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "entity.hh"
#include "sound.hh"

class Object : public Entity{
using Entity::Entity;
public:
	~Object(){};
	Sound* colSound;
	virtual void Update(float dt)  = 0;
};
