#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "coin.hh"
#include "player.hh"

void Player::Update(const Uint8 *keyState, float dt)
{
	//definition du Keys
	key = SDL_SCANCODE_SPACE;


	//Si le joueur appuie sur la barre espace, on monte
	if(keyState[key]){

		if (posY > 0.0){
			posY -= moveSpeed * dt;
		}
		else{
			posY = 0;
		}

		cRect.y = 0;
	}
	//Sinon ca descend
	else{

		if ((posY + posRect.h) < 480){
			posY += moveSpeed * dt;
		}
		else{
			posY = (480 - posRect.h);
		}
		cRect.y = frameHeight;
	}

	//Partie Changement texture
	frameCounter += dt;

	if(frameCounter >= 0.25f)
	{
		frameCounter = 0;
		cRect.x += frameWidth;
		if(cRect.x >= textureWidth){
			cRect.x = 0; //On retourne au frame initial
		}
	}

}


