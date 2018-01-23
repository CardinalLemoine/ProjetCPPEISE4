#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "entity.hh"

class Background : public Entity{

using Entity::Entity;

public:
	void Update(float dt);

};
