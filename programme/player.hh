#pragma once

#include <SDL2/SDL.h>
#include <string>
#include "entity.hh"
#include "coin.hh"
class Player : public Entity{

using Entity::Entity;

public:
	void Update(const Uint8 *keyState, float dt);

protected:
	SDL_Scancode key;

};
